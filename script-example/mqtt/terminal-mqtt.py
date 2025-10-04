
#!/usr/bin/env python3
"""PyQt5-based MQTT test harness offering connection management, subscriptions,
publishing, and automated test scenarios through a graphical interface."""

from __future__ import annotations

import argparse
import json
import logging
import os
import ssl
import sys
import threading
import time
from copy import deepcopy
from dataclasses import dataclass
from pathlib import Path
from queue import Empty, Queue
from typing import Any, Dict, List, Optional, Sequence, Tuple

try:
    from PyQt5 import QtCore, QtGui, QtWidgets
except ImportError as exc:
    print("PyQt5 is required. Install it with 'pip install PyQt5'.", file=sys.stderr)
    raise SystemExit(1) from exc

try:
    import paho.mqtt.client as mqtt
except ImportError as exc:
    print("The 'paho-mqtt' package is required. Install it with 'pip install paho-mqtt'.", file=sys.stderr)
    raise SystemExit(1) from exc


PROTOCOL_MAP = {
    "3.1": mqtt.MQTTv31,
    "3.1.1": mqtt.MQTTv311,
    "5": mqtt.MQTTv5,
}

TLS_VERSION_MAP: Dict[str, Optional[int]] = {
    "SYSTEM_DEFAULT": None,
    "TLS": getattr(ssl, "PROTOCOL_TLS_CLIENT", ssl.PROTOCOL_TLS),
    "TLSV1": getattr(ssl, "PROTOCOL_TLSv1", ssl.PROTOCOL_TLS),
    "TLSV1_1": getattr(ssl, "PROTOCOL_TLSv1_1", ssl.PROTOCOL_TLS),
    "TLSV1_2": getattr(ssl, "PROTOCOL_TLSv1_2", ssl.PROTOCOL_TLS),
    "TLSV1_3": getattr(ssl, "PROTOCOL_TLSv1_3", getattr(ssl, "PROTOCOL_TLS", None)),
}

DEFAULT_CONFIG: Dict[str, Any] = {
    "connection": {
        "host": "localhost",
        "port": 1883,
        "client_id": "",
        "keepalive": 60,
        "clean_session": True,
        "protocol": "3.1.1",
        "transport": "tcp",
        "reconnect_delay_min": 1,
        "reconnect_delay_max": 120,
        "reconnect_exponential_backoff": False,
    },
    "auth": {
        "username": None,
        "password": None,
        "tls": {
            "enabled": False,
            "ca_certs": None,
            "certfile": None,
            "keyfile": None,
            "tls_version": "SYSTEM_DEFAULT",
            "ciphers": None,
            "insecure": False,
        },
    },
    "last_will": {
        "topic": None,
        "payload": "",
        "qos": 0,
        "retain": False,
    },
    "subscriptions": [],
    "publishes": [],
    "auto_test": {
        "enabled": False,
        "count": 1,
        "interval": 1.0,
        "wait_after": 2.0,
    },
    "auto_connect": True,
    "message_log_limit": 100,
    "log_level": "INFO",
}

@dataclass
class Subscription:
    topic: str
    qos: int = 0

    @classmethod
    def from_any(cls, value: Any) -> "Subscription":
        if isinstance(value, Subscription):
            return value
        if isinstance(value, str):
            topic, qos = parse_subscription_string(value)
            return cls(topic=topic, qos=qos)
        if isinstance(value, dict):
            topic = value.get("topic")
            if not topic:
                raise ValueError("Subscription entry missing 'topic'.")
            qos = int(value.get("qos", 0))
            return cls(topic=str(topic), qos=qos)
        raise TypeError(f"Unsupported subscription entry type: {type(value)!r}")

    def as_dict(self) -> Dict[str, Any]:
        return {"topic": self.topic, "qos": self.qos}


@dataclass
class PublishRequest:
    topic: str
    payload: str
    qos: int = 0
    retain: bool = False

    @classmethod
    def from_any(cls, value: Any) -> "PublishRequest":
        if isinstance(value, PublishRequest):
            return value
        if isinstance(value, str):
            topic, payload, qos, retain = parse_publish_string(value)
            return cls(topic=topic, payload=payload, qos=qos, retain=retain)
        if isinstance(value, dict):
            topic = value.get("topic")
            if not topic:
                raise ValueError("Publish entry missing 'topic'.")
            payload = value.get("payload", "")
            qos = int(value.get("qos", 0))
            retain = bool(value.get("retain", False))
            return cls(topic=str(topic), payload=str(payload), qos=qos, retain=retain)
        raise TypeError(f"Unsupported publish entry type: {type(value)!r}")

    def as_dict(self) -> Dict[str, Any]:
        return {
            "topic": self.topic,
            "payload": self.payload,
            "qos": self.qos,
            "retain": self.retain,
        }


def parse_bool(value: str) -> bool:
    truthy = {"1", "true", "yes", "on", "retain"}
    falsy = {"0", "false", "no", "off"}
    normalized = value.strip().lower()
    if normalized in truthy:
        return True
    if normalized in falsy:
        return False
    raise ValueError(f"Cannot interpret '{value}' as boolean.")


def parse_subscription_string(raw: str) -> Tuple[str, int]:
    if "::" in raw:
        topic, *rest = raw.split("::")
    elif ":" in raw:
        topic, *rest = raw.split(":", 1)
    else:
        return raw.strip(), 0
    topic = topic.strip()
    qos = int(rest[0]) if rest and rest[0] else 0
    return topic, qos


def parse_publish_string(raw: str) -> Tuple[str, str, int, bool]:
    parts = raw.split("::")
    if len(parts) < 2:
        raise ValueError("Publish string must be 'topic::payload[::qos[::retain]]'.")
    topic = parts[0].strip()
    payload = parts[1]
    qos = int(parts[2]) if len(parts) > 2 and parts[2] else 0
    retain = False
    if len(parts) > 3 and parts[3]:
        retain = parse_bool(parts[3])
    return topic, payload, qos, retain


def truncate_payload(payload: bytes, limit: int = 120) -> str:
    if not payload:
        return "<empty>"
    try:
        text = payload.decode("utf-8")
        if len(text) > limit:
            return f"{text[:limit]}... ({len(payload)} bytes)"
        return text
    except UnicodeDecodeError:
        preview = payload[: min(limit // 2, len(payload))]
        hex_preview = preview.hex()
        if len(payload) > len(preview):
            return f"0x{hex_preview}... ({len(payload)} bytes)"
        return f"0x{hex_preview}"


def coerce_optional_path(value: Optional[str]) -> Optional[str]:
    if not value:
        return None
    return str(Path(os.path.expanduser(value)).resolve())


def translate_tls_version(value: Optional[str]) -> Optional[int]:
    if not value:
        return None
    key = value.upper()
    if key not in TLS_VERSION_MAP:
        raise ValueError(
            f"Unknown TLS version '{value}'. Choose from {', '.join(sorted(TLS_VERSION_MAP))}.",
        )
    return TLS_VERSION_MAP[key]


def deep_merge(base: Dict[str, Any], override: Dict[str, Any]) -> Dict[str, Any]:
    result = deepcopy(base)
    for key, value in override.items():
        if key in result and isinstance(result[key], dict) and isinstance(value, dict):
            result[key] = deep_merge(result[key], value)
        else:
            result[key] = value
    return result


def load_config(path: Optional[str]) -> Dict[str, Any]:
    if not path:
        return {}
    config_path = Path(os.path.expanduser(path)).resolve()
    if not config_path.exists():
        raise FileNotFoundError(f"Config file not found: {config_path}")
    with config_path.open("r", encoding="utf-8") as handle:
        try:
            return json.load(handle)
        except json.JSONDecodeError as exc:
            raise ValueError(f"Failed to parse config '{config_path}': {exc}") from exc


def normalise_settings(config: Dict[str, Any]) -> Dict[str, Any]:
    config["subscriptions"] = [Subscription.from_any(entry) for entry in config.get("subscriptions", [])]
    config["publishes"] = [PublishRequest.from_any(entry) for entry in config.get("publishes", [])]
    auto = config.setdefault("auto_test", {})
    auto.setdefault("enabled", False)
    auto.setdefault("count", 1)
    auto.setdefault("interval", 1.0)
    auto.setdefault("wait_after", 2.0)
    config.setdefault("message_log_limit", 100)
    config.setdefault("log_level", "INFO")
    return config


def apply_cli_overrides(config: Dict[str, Any], args: argparse.Namespace) -> Dict[str, Any]:
    connection = config.setdefault("connection", {})
    if args.host:
        connection["host"] = args.host
    if args.port is not None:
        connection["port"] = args.port
    if args.client_id is not None:
        connection["client_id"] = args.client_id
    if args.keepalive is not None:
        connection["keepalive"] = args.keepalive
    if args.clean_session is not None:
        connection["clean_session"] = args.clean_session
    if args.protocol:
        connection["protocol"] = args.protocol
    if args.transport:
        connection["transport"] = args.transport
    if args.reconnect_delay_min is not None:
        connection["reconnect_delay_min"] = max(args.reconnect_delay_min, 0)
    if args.reconnect_delay_max is not None:
        connection["reconnect_delay_max"] = max(args.reconnect_delay_max, 0)
    if args.reconnect_exponential_backoff is not None:
        connection["reconnect_exponential_backoff"] = args.reconnect_exponential_backoff

    auth = config.setdefault("auth", {})
    if args.username is not None:
        auth["username"] = args.username
    if args.password is not None:
        auth["password"] = args.password

    tls_cfg = auth.setdefault("tls", {})
    if args.tls is not None:
        tls_cfg["enabled"] = args.tls
    if args.ca_certs is not None:
        tls_cfg["ca_certs"] = args.ca_certs
    if args.certfile is not None:
        tls_cfg["certfile"] = args.certfile
    if args.keyfile is not None:
        tls_cfg["keyfile"] = args.keyfile
    if args.tls_version is not None:
        tls_cfg["tls_version"] = args.tls_version
    if args.ciphers is not None:
        tls_cfg["ciphers"] = args.ciphers
    if args.insecure is not None:
        tls_cfg["insecure"] = args.insecure

    last_will = config.setdefault("last_will", {})
    if args.will_topic is not None:
        last_will["topic"] = args.will_topic
    if args.will_payload is not None:
        last_will["payload"] = args.will_payload
    if args.will_qos is not None:
        last_will["qos"] = args.will_qos
    if args.will_retain is not None:
        last_will["retain"] = args.will_retain

    if args.subscribe:
        config.setdefault("subscriptions", [])
        config["subscriptions"].extend(args.subscribe)
    if args.publish:
        config.setdefault("publishes", [])
        config["publishes"].extend(args.publish)

    auto_test = config.setdefault("auto_test", {})
    if args.auto is not None:
        auto_test["enabled"] = args.auto
    if args.auto_count is not None:
        auto_test["count"] = max(1, args.auto_count)
    if args.auto_interval is not None:
        auto_test["interval"] = max(0.0, args.auto_interval)
    if args.auto_wait is not None:
        auto_test["wait_after"] = max(0.0, args.auto_wait)

    if args.auto_connect is not None:
        config["auto_connect"] = args.auto_connect
    if args.message_log_limit is not None:
        config["message_log_limit"] = max(1, args.message_log_limit)
    if args.log_level is not None:
        config["log_level"] = args.log_level

    return config


def setup_logging(level: Optional[str], quiet: bool) -> None:
    if quiet:
        resolved = logging.WARNING
    elif level:
        resolved = logging.getLevelName(level.upper())
        if isinstance(resolved, str):
            raise ValueError(f"Unknown log level '{level}'.")
    else:
        resolved = logging.INFO
    logging.basicConfig(
        level=resolved,
        format="%(asctime)s %(levelname)-8s %(message)s",
        datefmt="%Y-%m-%d %H:%M:%S",
    )

class MQTTTerminal:
    def __init__(
        self,
        settings: Dict[str, Any],
        *,
        event_queue: Optional["Queue[Tuple[str, Dict[str, Any]]]"] = None,
    ) -> None:
        self.settings = settings
        self.logger = logging.getLogger("terminal-mqtt")
        self._event_queue: "Queue[Tuple[str, Dict[str, Any]]]" = event_queue or Queue()
        self._message_queue: "Queue[Dict[str, Any]]" = Queue()
        self._client = self._build_client()
        self._connected = threading.Event()
        self._disconnected = threading.Event()
        self._stop = threading.Event()
        self._subscriptions: Dict[str, int] = {sub.topic: sub.qos for sub in settings.get("subscriptions", [])}
        self._pending_subscriptions: Dict[int, Tuple[str, int]] = {}
        self._pending_unsubscriptions: Dict[int, str] = {}
        self._pending_publishes: Dict[int, PublishRequest] = {}
        self._message_log: List[Dict[str, Any]] = []
        self._loop_started = False
        self._lock = threading.Lock()

    @property
    def client(self) -> mqtt.Client:
        return self._client

    @property
    def is_connected(self) -> bool:
        return self._connected.is_set() and not self._disconnected.is_set()

    def drain_events(self) -> List[Tuple[str, Dict[str, Any]]]:
        events: List[Tuple[str, Dict[str, Any]]] = []
        while True:
            try:
                events.append(self._event_queue.get_nowait())
            except Empty:
                break
        return events

    def drain_messages(self) -> List[Dict[str, Any]]:
        items: List[Dict[str, Any]] = []
        while True:
            try:
                items.append(self._message_queue.get_nowait())
            except Empty:
                break
        return items

    def emit_event(self, event: str, payload: Dict[str, Any]) -> None:
        self._event_queue.put((event, payload))

    def _build_client(self) -> mqtt.Client:
        connection = self.settings.get("connection", {})
        protocol_name = str(connection.get("protocol", "3.1.1"))
        protocol = PROTOCOL_MAP.get(protocol_name)
        if protocol is None:
            raise ValueError(
                f"Unsupported MQTT protocol '{protocol_name}'. Valid options: {', '.join(PROTOCOL_MAP)}.",
            )
        client_id = connection.get("client_id") or None
        transport = connection.get("transport", "tcp")
        clean_session = connection.get("clean_session", True)
        if protocol == mqtt.MQTTv5:
            client = mqtt.Client(client_id=client_id, protocol=protocol, transport=transport)
        else:
            client = mqtt.Client(
                client_id=client_id,
                clean_session=bool(clean_session),
                protocol=protocol,
                transport=transport,
            )
        reconnect_min = max(int(connection.get("reconnect_delay_min", 1)), 0)
        reconnect_max = max(int(connection.get("reconnect_delay_max", 120)), reconnect_min)
        client.reconnect_delay_set(reconnect_min, reconnect_max)
        if connection.get("reconnect_exponential_backoff"):
            try:
                client.reconnect_delay_set(reconnect_min, reconnect_max, exponential=True)  # type: ignore[arg-type]
            except TypeError:
                self.logger.debug("paho-mqtt installation does not support exponential reconnect configuration.")
        client.enable_logger(logging.getLogger("paho"))
        self._configure_authentication(client)
        self._configure_last_will(client)
        self._assign_callbacks(client)
        return client

    def _configure_authentication(self, client: mqtt.Client) -> None:
        auth = self.settings.get("auth", {})
        username = auth.get("username")
        password = auth.get("password")
        if username is not None or password is not None:
            client.username_pw_set(username=username, password=password)
        tls_cfg = auth.get("tls", {})
        wants_tls = any(
            bool(tls_cfg.get(field))
            for field in ("enabled", "ca_certs", "certfile", "keyfile", "ciphers")
        )
        if wants_tls:
            tls_kwargs: Dict[str, Any] = {
                "ca_certs": coerce_optional_path(tls_cfg.get("ca_certs")),
                "certfile": coerce_optional_path(tls_cfg.get("certfile")),
                "keyfile": coerce_optional_path(tls_cfg.get("keyfile")),
                "ciphers": tls_cfg.get("ciphers"),
            }
            tls_version_value = tls_cfg.get("tls_version")
            try:
                tls_kwargs["tls_version"] = translate_tls_version(tls_version_value)
            except ValueError as exc:
                raise SystemExit(str(exc)) from exc
            try:
                client.tls_set(**tls_kwargs)
            except ssl.SSLError as exc:
                raise SystemExit(f"TLS configuration failed: {exc}") from exc
            client.tls_insecure_set(bool(tls_cfg.get("insecure", False)))

    def _configure_last_will(self, client: mqtt.Client) -> None:
        last_will = self.settings.get("last_will", {})
        topic = last_will.get("topic")
        if topic:
            payload = last_will.get("payload", "")
            qos = int(last_will.get("qos", 0))
            retain = bool(last_will.get("retain", False))
            client.will_set(topic, payload=payload, qos=qos, retain=retain)

    def _assign_callbacks(self, client: mqtt.Client) -> None:
        client.on_connect = self._on_connect
        client.on_disconnect = self._on_disconnect
        client.on_message = self._on_message
        client.on_subscribe = self._on_subscribe
        client.on_unsubscribe = self._on_unsubscribe
        client.on_publish = self._on_publish
        client.on_log = self._on_log if logging.getLogger().isEnabledFor(logging.DEBUG) else None
    def _on_connect(self, client: mqtt.Client, userdata: Any, flags: Dict[str, Any], rc: int, properties: Any = None) -> None:
        reason = mqtt.connack_string(rc)
        if rc == mqtt.CONNACK_ACCEPTED:
            self.logger.info(
                "Connected to %s:%s (%s)",
                self.settings["connection"].get("host"),
                self.settings["connection"].get("port"),
                reason,
            )
            self._disconnected.clear()
            self._connected.set()
            self.emit_event(
                "connect",
                {
                    "host": self.settings["connection"].get("host"),
                    "port": self.settings["connection"].get("port"),
                    "reason": reason,
                },
            )
            self._restore_subscriptions()
        else:
            self.logger.error("Connection refused: %s", reason)
            self._connected.clear()
            self.emit_event("connect_error", {"code": rc, "reason": reason})

    def _on_disconnect(self, client: mqtt.Client, userdata: Any, rc: int, properties: Any = None) -> None:
        if rc == mqtt.MQTT_ERR_SUCCESS:
            self.logger.info("Disconnected cleanly.")
        else:
            self.logger.warning("Disconnected unexpectedly (rc=%s).", rc)
        self._connected.clear()
        self._disconnected.set()
        self.emit_event("disconnect", {"rc": rc})

    def _on_message(self, client: mqtt.Client, userdata: Any, message: mqtt.MQTTMessage) -> None:
        record = {
            "timestamp": time.time(),
            "topic": message.topic,
            "payload": message.payload,
            "qos": message.qos,
            "retain": message.retain,
        }
        self._message_queue.put(record)
        self._message_log.append(record)
        limit = self.settings.get("message_log_limit", 100)
        if len(self._message_log) > limit:
            self._message_log = self._message_log[-limit:]
        self.emit_event("message", record)

    def _on_subscribe(self, client: mqtt.Client, userdata: Any, mid: int, granted_qos: Sequence[int]) -> None:
        with self._lock:
            info = self._pending_subscriptions.pop(mid, None)
            if info:
                topic, requested_qos = info
                new_qos = granted_qos[0] if granted_qos else requested_qos
                self._subscriptions[topic] = new_qos
                self.logger.info("Subscribed to '%s' (granted QoS %s).", topic, new_qos)
                self.emit_event("subscribed", {"topic": topic, "qos": new_qos})

    def _on_unsubscribe(self, client: mqtt.Client, userdata: Any, mid: int) -> None:
        with self._lock:
            topic = self._pending_unsubscriptions.pop(mid, None)
            if topic:
                self._subscriptions.pop(topic, None)
                self.logger.info("Unsubscribed from '%s'.", topic)
                self.emit_event("unsubscribed", {"topic": topic})

    def _on_publish(self, client: mqtt.Client, userdata: Any, mid: int) -> None:
        with self._lock:
            request = self._pending_publishes.pop(mid, None)
            if request:
                self.logger.debug("Publish acknowledged for topic '%s'.", request.topic)
                self.emit_event("publish_ack", {"topic": request.topic})

    def _on_log(self, client: mqtt.Client, userdata: Any, level: int, buf: str) -> None:  # pragma: no cover - debug aid
        logging.getLogger("paho-debug").debug("paho: %s", buf)

    def connect(self, timeout: float = 15.0) -> None:
        connection = self.settings.get("connection", {})
        host = connection.get("host", "localhost")
        port = int(connection.get("port", 1883))
        keepalive = int(connection.get("keepalive", 60))
        self.logger.debug("Initiating connection to %s:%s (keepalive %s).", host, port, keepalive)
        self._connected.clear()
        self._disconnected.clear()
        try:
            result = self._client.connect(host, port, keepalive)
        except Exception as exc:
            raise RuntimeError(f"Failed to connect to {host}:{port} -> {exc}") from exc
        if result != mqtt.MQTT_ERR_SUCCESS:
            raise RuntimeError(
                f"Connection initiation failed: {mqtt.error_string(result)} ({result}).",
            )
        if not self._loop_started:
            self._client.loop_start()
            self._loop_started = True
        if timeout > 0:
            if not self._connected.wait(timeout):
                raise TimeoutError(f"Timed out after {timeout} seconds waiting for broker acknowledgement.")

    def disconnect(self, timeout: float = 5.0) -> None:
        if not self._loop_started:
            return
        self.logger.debug("Disconnect requested.")
        self._disconnected.clear()
        self._client.disconnect()
        if timeout > 0:
            self._disconnected.wait(timeout)

    def stop(self) -> None:
        self._stop.set()
        try:
            self.disconnect()
        finally:
            if self._loop_started:
                self._client.loop_stop()
                self._loop_started = False

    def subscribe(self, topic: str, qos: int = 0) -> None:
        if not topic:
            raise ValueError("Topic cannot be empty.")
        qos = max(0, min(2, qos))
        result, mid = self._client.subscribe(topic, qos)
        if result != mqtt.MQTT_ERR_SUCCESS:
            raise RuntimeError(f"Subscribe failed: {mqtt.error_string(result)}")
        with self._lock:
            self._pending_subscriptions[mid] = (topic, qos)

    def unsubscribe(self, topic: str) -> None:
        if not topic:
            raise ValueError("Topic cannot be empty.")
        result, mid = self._client.unsubscribe(topic)
        if result != mqtt.MQTT_ERR_SUCCESS:
            raise RuntimeError(f"Unsubscribe failed: {mqtt.error_string(result)}")
        with self._lock:
            self._pending_unsubscriptions[mid] = topic

    def publish(self, request: PublishRequest) -> None:
        info = self._client.publish(request.topic, payload=request.payload, qos=request.qos, retain=request.retain)
        if info.rc != mqtt.MQTT_ERR_SUCCESS:
            raise RuntimeError(f"Publish failed: {mqtt.error_string(info.rc)}")
        with self._lock:
            self._pending_publishes[info.mid] = request

    def _restore_subscriptions(self) -> None:
        if not self._subscriptions:
            return
        for topic, qos in list(self._subscriptions.items()):
            try:
                self.subscribe(topic, qos)
            except RuntimeError as exc:
                self.logger.error("Failed to resubscribe to '%s': %s", topic, exc)

    def run_auto_tests(self, count: int, interval: float, wait_after: float) -> None:
        if not self.is_connected:
            self.connect()
        if not self.settings.get("publishes"):
            self.emit_event("auto_warning", {"message": "No publish entries configured for auto test."})
            return
        for iteration in range(count):
            for request in self.settings["publishes"]:
                self.publish(request)
            if interval and iteration + 1 < count:
                time.sleep(interval)
        if wait_after:
            time.sleep(wait_after)
        self.emit_event("auto_complete", {"count": count})

class GuiLogHandler(logging.Handler):
    def __init__(self, event_queue: "Queue[Tuple[str, Dict[str, Any]]]") -> None:
        super().__init__()
        self._queue = event_queue

    def emit(self, record: logging.LogRecord) -> None:  # pragma: no cover - GUI helper
        try:
            message = self.format(record)
        except Exception:
            message = record.getMessage()
        payload = {
            "timestamp": time.time(),
            "level": record.levelname,
            "message": message,
        }
        self._queue.put(("log", payload))


class MQTTMainWindow(QtWidgets.QMainWindow):
    LOG_LIMIT = 500

    def __init__(self, settings: Dict[str, Any], *, no_connect: bool, timeout: float) -> None:
        super().__init__()
        self.setWindowTitle("Delta X Software MQTT Tester")
        self.resize(1200, 800)
        self.settings = deepcopy(settings)
        self._no_connect = no_connect
        self._connect_timeout = timeout
        self._event_queue: "Queue[Tuple[str, Dict[str, Any]]]" = Queue()
        self.terminal: Optional[MQTTTerminal] = None
        self._subscriptions: List[Subscription] = []
        self._auto_publishes: List[PublishRequest] = []
        self._log_buffer: List[str] = []

        self._log_handler = GuiLogHandler(self._event_queue)
        self._log_handler.setLevel(logging.INFO)
        root_logger = logging.getLogger()
        root_logger.addHandler(self._log_handler)

        self._setup_ui()
        self._bind_signals()
        self._apply_settings_to_ui(self.settings)
        self._create_terminal(self.settings)

        self._timer = QtCore.QTimer(self)
        self._timer.setInterval(200)
        self._timer.timeout.connect(self._process_terminal_events)
        self._timer.start()

        if self.settings.get("auto_connect", True) and not self._no_connect:
            QtCore.QTimer.singleShot(300, self.handle_connect)
    def _setup_ui(self) -> None:
        central = QtWidgets.QWidget(self)
        self.setCentralWidget(central)
        main_layout = QtWidgets.QVBoxLayout(central)
        main_layout.setSpacing(8)
        main_layout.setContentsMargins(8, 8, 8, 8)

        self.connection_group = self._build_connection_group()
        main_layout.addWidget(self.connection_group)

        splitter = QtWidgets.QSplitter(QtCore.Qt.Horizontal, self)
        main_layout.addWidget(splitter, 1)

        left_panel = QtWidgets.QWidget()
        left_layout = QtWidgets.QVBoxLayout(left_panel)
        left_layout.setSpacing(8)
        left_layout.addWidget(self._build_subscription_group())
        left_layout.addWidget(self._build_publish_group())
        left_layout.addWidget(self._build_auto_group())
        left_layout.addStretch()
        splitter.addWidget(left_panel)

        right_panel = QtWidgets.QWidget()
        right_layout = QtWidgets.QVBoxLayout(right_panel)
        right_layout.setSpacing(8)
        right_layout.addWidget(self._build_messages_group())
        right_layout.addWidget(self._build_log_group())
        splitter.addWidget(right_panel)

        splitter.setStretchFactor(0, 0)
        splitter.setStretchFactor(1, 1)

    def _build_connection_group(self) -> QtWidgets.QGroupBox:
        group = QtWidgets.QGroupBox("Connection")
        layout = QtWidgets.QGridLayout(group)
        layout.setHorizontalSpacing(8)
        layout.setVerticalSpacing(6)

        self.host_edit = QtWidgets.QLineEdit()
        self.port_spin = QtWidgets.QSpinBox()
        self.port_spin.setRange(1, 65535)
        self.port_spin.setValue(1883)
        self.client_id_edit = QtWidgets.QLineEdit()
        self.keepalive_spin = QtWidgets.QSpinBox()
        self.keepalive_spin.setRange(0, 65535)
        self.keepalive_spin.setValue(60)
        self.protocol_combo = QtWidgets.QComboBox()
        self.protocol_combo.addItems(sorted(PROTOCOL_MAP.keys()))
        self.transport_combo = QtWidgets.QComboBox()
        self.transport_combo.addItems(["tcp", "websockets"])
        self.clean_session_checkbox = QtWidgets.QCheckBox("Clean session")
        self.clean_session_checkbox.setChecked(True)

        self.username_edit = QtWidgets.QLineEdit()
        self.password_edit = QtWidgets.QLineEdit()
        self.password_edit.setEchoMode(QtWidgets.QLineEdit.Password)

        self.tls_checkbox = QtWidgets.QCheckBox("Enable TLS")
        self.ca_path_edit, ca_button = self._make_path_input()
        self.cert_path_edit, cert_button = self._make_path_input()
        self.key_path_edit, key_button = self._make_path_input()
        self.tls_version_combo = QtWidgets.QComboBox()
        self.tls_version_combo.addItems(sorted(TLS_VERSION_MAP.keys()))
        self.ciphers_edit = QtWidgets.QLineEdit()
        self.insecure_checkbox = QtWidgets.QCheckBox("Allow insecure (skip cert validation)")

        self.will_topic_edit = QtWidgets.QLineEdit()
        self.will_payload_edit = QtWidgets.QLineEdit()
        self.will_qos_spin = QtWidgets.QSpinBox()
        self.will_qos_spin.setRange(0, 2)
        self.will_retain_checkbox = QtWidgets.QCheckBox("Retain")

        self.auto_connect_checkbox = QtWidgets.QCheckBox("Auto connect on launch")
        self.auto_connect_checkbox.setChecked(True)
        self.timeout_spin = QtWidgets.QDoubleSpinBox()
        self.timeout_spin.setRange(0.1, 300.0)
        self.timeout_spin.setDecimals(1)
        self.timeout_spin.setValue(self._connect_timeout)
        self.message_limit_spin = QtWidgets.QSpinBox()
        self.message_limit_spin.setRange(10, 10000)
        self.message_limit_spin.setValue(100)
        self.log_level_combo = QtWidgets.QComboBox()
        self.log_level_combo.addItems(["DEBUG", "INFO", "WARNING", "ERROR", "CRITICAL"])

        self.connect_button = QtWidgets.QPushButton("Connect")
        self.disconnect_button = QtWidgets.QPushButton("Disconnect")
        self.status_label = QtWidgets.QLabel("Disconnected")
        self.status_label.setStyleSheet("color: #b03030;")

        row = 0
        layout.addWidget(QtWidgets.QLabel("Host"), row, 0)
        layout.addWidget(self.host_edit, row, 1)
        layout.addWidget(QtWidgets.QLabel("Port"), row, 2)
        layout.addWidget(self.port_spin, row, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Client ID"), row, 0)
        layout.addWidget(self.client_id_edit, row, 1)
        layout.addWidget(QtWidgets.QLabel("Keepalive"), row, 2)
        layout.addWidget(self.keepalive_spin, row, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Protocol"), row, 0)
        layout.addWidget(self.protocol_combo, row, 1)
        layout.addWidget(QtWidgets.QLabel("Transport"), row, 2)
        layout.addWidget(self.transport_combo, row, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel(""), row, 0)
        layout.addWidget(self.clean_session_checkbox, row, 1)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Username"), row, 0)
        layout.addWidget(self.username_edit, row, 1)
        layout.addWidget(QtWidgets.QLabel("Password"), row, 2)
        layout.addWidget(self.password_edit, row, 3)
        row += 1
        layout.addWidget(self.tls_checkbox, row, 0, 1, 2)
        row += 1
        layout.addWidget(QtWidgets.QLabel("CA cert"), row, 0)
        layout.addLayout(self._wrap_with_button(self.ca_path_edit, ca_button), row, 1)
        layout.addWidget(QtWidgets.QLabel("Client cert"), row, 2)
        layout.addLayout(self._wrap_with_button(self.cert_path_edit, cert_button), row, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Client key"), row, 0)
        layout.addLayout(self._wrap_with_button(self.key_path_edit, key_button), row, 1)
        layout.addWidget(QtWidgets.QLabel("TLS version"), row, 2)
        layout.addWidget(self.tls_version_combo, row, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Ciphers"), row, 0)
        layout.addWidget(self.ciphers_edit, row, 1, 1, 3)
        row += 1
        layout.addWidget(self.insecure_checkbox, row, 0, 1, 4)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Last will topic"), row, 0)
        layout.addWidget(self.will_topic_edit, row, 1)
        layout.addWidget(QtWidgets.QLabel("Payload"), row, 2)
        layout.addWidget(self.will_payload_edit, row, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Will QoS"), row, 0)
        layout.addWidget(self.will_qos_spin, row, 1)
        layout.addWidget(self.will_retain_checkbox, row, 2)
        row += 1
        layout.addWidget(self.auto_connect_checkbox, row, 0, 1, 2)
        layout.addWidget(QtWidgets.QLabel("Timeout (s)"), row, 2)
        layout.addWidget(self.timeout_spin, row, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Message log limit"), row, 0)
        layout.addWidget(self.message_limit_spin, row, 1)
        layout.addWidget(QtWidgets.QLabel("Log level"), row, 2)
        layout.addWidget(self.log_level_combo, row, 3)
        row += 1
        layout.addWidget(self.connect_button, row, 0, 1, 2)
        layout.addWidget(self.disconnect_button, row, 2)
        layout.addWidget(self.status_label, row, 3)

        self._toggle_tls_inputs(False)
        return group
    def _wrap_with_button(self, line_edit: QtWidgets.QLineEdit, button: QtWidgets.QToolButton) -> QtWidgets.QHBoxLayout:
        layout = QtWidgets.QHBoxLayout()
        layout.setContentsMargins(0, 0, 0, 0)
        layout.addWidget(line_edit)
        layout.addWidget(button)
        return layout

    def _make_path_input(self) -> Tuple[QtWidgets.QLineEdit, QtWidgets.QToolButton]:
        edit = QtWidgets.QLineEdit()
        button = QtWidgets.QToolButton()
        button.setText("...")
        button.clicked.connect(lambda _=None, e=edit: self._browse_for_file(e))
        return edit, button

    def _browse_for_file(self, target: QtWidgets.QLineEdit) -> None:
        path, _ = QtWidgets.QFileDialog.getOpenFileName(self, "Select file", target.text() or str(Path.home()))
        if path:
            target.setText(path)

    def _build_subscription_group(self) -> QtWidgets.QGroupBox:
        group = QtWidgets.QGroupBox("Subscriptions")
        layout = QtWidgets.QVBoxLayout(group)
        layout.setSpacing(6)

        self.subscription_table = QtWidgets.QTableWidget(0, 2)
        self.subscription_table.setHorizontalHeaderLabels(["Topic", "QoS"])
        self.subscription_table.horizontalHeader().setStretchLastSection(True)
        self.subscription_table.setSelectionBehavior(QtWidgets.QAbstractItemView.SelectRows)
        self.subscription_table.setSelectionMode(QtWidgets.QAbstractItemView.SingleSelection)
        self.subscription_table.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        layout.addWidget(self.subscription_table)

        form = QtWidgets.QHBoxLayout()
        self.sub_topic_edit = QtWidgets.QLineEdit()
        self.sub_topic_edit.setPlaceholderText("Topic filter")
        self.sub_qos_spin = QtWidgets.QSpinBox()
        self.sub_qos_spin.setRange(0, 2)
        self.sub_add_button = QtWidgets.QPushButton("Add / Update")
        self.sub_remove_button = QtWidgets.QPushButton("Remove Selected")
        form.addWidget(self.sub_topic_edit, 2)
        form.addWidget(QtWidgets.QLabel("QoS"))
        form.addWidget(self.sub_qos_spin)
        form.addWidget(self.sub_add_button)
        form.addWidget(self.sub_remove_button)
        layout.addLayout(form)
        return group

    def _build_publish_group(self) -> QtWidgets.QGroupBox:
        group = QtWidgets.QGroupBox("Publish")
        layout = QtWidgets.QGridLayout(group)
        layout.setHorizontalSpacing(6)
        layout.setVerticalSpacing(4)

        self.pub_topic_edit = QtWidgets.QLineEdit()
        self.pub_payload_edit = QtWidgets.QPlainTextEdit()
        self.pub_payload_edit.setPlaceholderText("Message payload")
        self.pub_payload_edit.setFixedHeight(80)
        self.pub_qos_spin = QtWidgets.QSpinBox()
        self.pub_qos_spin.setRange(0, 2)
        self.pub_retain_checkbox = QtWidgets.QCheckBox("Retain")
        self.pub_count_spin = QtWidgets.QSpinBox()
        self.pub_count_spin.setRange(1, 1000)
        self.pub_count_spin.setValue(1)
        self.pub_interval_spin = QtWidgets.QDoubleSpinBox()
        self.pub_interval_spin.setRange(0.0, 3600.0)
        self.pub_interval_spin.setDecimals(2)
        self.pub_interval_spin.setValue(0.0)
        self.publish_button = QtWidgets.QPushButton("Publish")

        row = 0
        layout.addWidget(QtWidgets.QLabel("Topic"), row, 0)
        layout.addWidget(self.pub_topic_edit, row, 1, 1, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Payload"), row, 0)
        layout.addWidget(self.pub_payload_edit, row, 1, 1, 3)
        row += 1
        layout.addWidget(QtWidgets.QLabel("QoS"), row, 0)
        layout.addWidget(self.pub_qos_spin, row, 1)
        layout.addWidget(self.pub_retain_checkbox, row, 2)
        row += 1
        layout.addWidget(QtWidgets.QLabel("Count"), row, 0)
        layout.addWidget(self.pub_count_spin, row, 1)
        layout.addWidget(QtWidgets.QLabel("Interval (s)"), row, 2)
        layout.addWidget(self.pub_interval_spin, row, 3)
        row += 1
        layout.addWidget(self.publish_button, row, 0, 1, 4)
        return group

    def _build_auto_group(self) -> QtWidgets.QGroupBox:
        group = QtWidgets.QGroupBox("Auto Test")
        layout = QtWidgets.QVBoxLayout(group)
        layout.setSpacing(6)

        self.auto_enabled_checkbox = QtWidgets.QCheckBox("Enable auto test after connect")
        layout.addWidget(self.auto_enabled_checkbox)

        self.auto_table = QtWidgets.QTableWidget(0, 4)
        self.auto_table.setHorizontalHeaderLabels(["Topic", "Payload", "QoS", "Retain"])
        self.auto_table.horizontalHeader().setStretchLastSection(True)
        self.auto_table.setSelectionBehavior(QtWidgets.QAbstractItemView.SelectRows)
        self.auto_table.setSelectionMode(QtWidgets.QAbstractItemView.SingleSelection)
        self.auto_table.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        layout.addWidget(self.auto_table)

        form = QtWidgets.QHBoxLayout()
        self.auto_topic_edit = QtWidgets.QLineEdit()
        self.auto_topic_edit.setPlaceholderText("Topic")
        self.auto_payload_edit = QtWidgets.QLineEdit()
        self.auto_payload_edit.setPlaceholderText("Payload")
        self.auto_qos_spin = QtWidgets.QSpinBox()
        self.auto_qos_spin.setRange(0, 2)
        self.auto_retain_checkbox = QtWidgets.QCheckBox("Retain")
        self.auto_add_button = QtWidgets.QPushButton("Add / Update")
        self.auto_remove_button = QtWidgets.QPushButton("Remove Selected")
        form.addWidget(self.auto_topic_edit, 2)
        form.addWidget(self.auto_payload_edit, 3)
        form.addWidget(QtWidgets.QLabel("QoS"))
        form.addWidget(self.auto_qos_spin)
        form.addWidget(self.auto_retain_checkbox)
        form.addWidget(self.auto_add_button)
        form.addWidget(self.auto_remove_button)
        layout.addLayout(form)

        grid = QtWidgets.QGridLayout()
        self.auto_count_spin = QtWidgets.QSpinBox()
        self.auto_count_spin.setRange(1, 1000)
        self.auto_count_spin.setValue(1)
        self.auto_interval_spin = QtWidgets.QDoubleSpinBox()
        self.auto_interval_spin.setRange(0.0, 3600.0)
        self.auto_interval_spin.setDecimals(2)
        self.auto_interval_spin.setValue(1.0)
        self.auto_wait_spin = QtWidgets.QDoubleSpinBox()
        self.auto_wait_spin.setRange(0.0, 3600.0)
        self.auto_wait_spin.setDecimals(2)
        self.auto_wait_spin.setValue(2.0)
        self.auto_run_button = QtWidgets.QPushButton("Run Auto Test")
        grid.addWidget(QtWidgets.QLabel("Iterations"), 0, 0)
        grid.addWidget(self.auto_count_spin, 0, 1)
        grid.addWidget(QtWidgets.QLabel("Interval (s)"), 0, 2)
        grid.addWidget(self.auto_interval_spin, 0, 3)
        grid.addWidget(QtWidgets.QLabel("Wait after (s)"), 1, 0)
        grid.addWidget(self.auto_wait_spin, 1, 1)
        grid.addWidget(self.auto_run_button, 1, 2, 1, 2)
        layout.addLayout(grid)
        return group
    def _build_messages_group(self) -> QtWidgets.QGroupBox:
        group = QtWidgets.QGroupBox("Received Messages")
        layout = QtWidgets.QVBoxLayout(group)
        layout.setSpacing(6)

        self.messages_table = QtWidgets.QTableWidget(0, 5)
        self.messages_table.setHorizontalHeaderLabels(["Time", "Topic", "Payload", "QoS", "Retain"])
        self.messages_table.horizontalHeader().setStretchLastSection(True)
        self.messages_table.setSelectionBehavior(QtWidgets.QAbstractItemView.SelectRows)
        self.messages_table.setEditTriggers(QtWidgets.QAbstractItemView.NoEditTriggers)
        layout.addWidget(self.messages_table)

        controls = QtWidgets.QHBoxLayout()
        self.clear_messages_button = QtWidgets.QPushButton("Clear")
        controls.addStretch(1)
        controls.addWidget(self.clear_messages_button)
        layout.addLayout(controls)
        return group

    def _build_log_group(self) -> QtWidgets.QGroupBox:
        group = QtWidgets.QGroupBox("Log")
        layout = QtWidgets.QVBoxLayout(group)
        layout.setSpacing(6)

        self.log_view = QtWidgets.QPlainTextEdit()
        self.log_view.setReadOnly(True)
        layout.addWidget(self.log_view)

        controls = QtWidgets.QHBoxLayout()
        self.clear_log_button = QtWidgets.QPushButton("Clear Log")
        controls.addStretch(1)
        controls.addWidget(self.clear_log_button)
        layout.addLayout(controls)
        return group

    def _bind_signals(self) -> None:
        self.tls_checkbox.toggled.connect(self._toggle_tls_inputs)
        self.connect_button.clicked.connect(self.handle_connect)
        self.disconnect_button.clicked.connect(self.handle_disconnect)
        self.sub_add_button.clicked.connect(self.handle_add_subscription)
        self.sub_remove_button.clicked.connect(self.handle_remove_subscription)
        self.publish_button.clicked.connect(self.handle_publish)
        self.clear_messages_button.clicked.connect(self.messages_table.clearContents)
        self.clear_messages_button.clicked.connect(lambda: self.messages_table.setRowCount(0))
        self.clear_log_button.clicked.connect(self._clear_log)
        self.auto_add_button.clicked.connect(self.handle_add_auto_publish)
        self.auto_remove_button.clicked.connect(self.handle_remove_auto_publish)
        self.auto_run_button.clicked.connect(self.handle_auto_run)
        self.log_level_combo.currentTextChanged.connect(self._on_log_level_changed)

    def _toggle_tls_inputs(self, enabled: bool) -> None:
        for widget in (
            self.ca_path_edit,
            self.cert_path_edit,
            self.key_path_edit,
            self.tls_version_combo,
            self.ciphers_edit,
            self.insecure_checkbox,
        ):
            widget.setEnabled(enabled)
    def _create_terminal(self, settings: Dict[str, Any]) -> None:
        if self.terminal:
            self.terminal.stop()
        self.terminal = MQTTTerminal(settings, event_queue=self._event_queue)
        self._subscriptions = [Subscription(sub.topic, sub.qos) for sub in settings.get("subscriptions", [])]
        self._auto_publishes = [
            PublishRequest(pub.topic, pub.payload, pub.qos, pub.retain) for pub in settings.get("publishes", [])
        ]
        self._refresh_subscription_table()
        self._refresh_auto_table()

    def _process_terminal_events(self) -> None:
        if not self.terminal:
            return
        for event, payload in self.terminal.drain_events():
            if event == "message":
                self._add_message_row(payload)
            elif event == "connect":
                self._set_status(True, payload.get("reason", ""))
                if self.auto_enabled_checkbox.isChecked():
                    self.handle_auto_run()
            elif event == "connect_error":
                self._set_status(False, payload.get("reason", ""))
            elif event == "disconnect":
                self._set_status(False, "Disconnected")
            elif event == "subscribed":
                self._update_subscription_ack(payload)
            elif event == "unsubscribed":
                self._remove_subscription_row(payload.get("topic"))
            elif event == "publish_ack":
                self._append_log(f"Publish acknowledged for {payload.get('topic')}")
            elif event == "auto_warning":
                self._append_log(payload.get("message", "Auto test warning"))
            elif event == "auto_complete":
                self._append_log("Auto test finished")
            elif event == "log":
                self._append_log(self._format_log_payload(payload))
            elif event == "error":
                self._show_error(payload.get("message", "Unknown error"))
        self.terminal.drain_messages()
        self._update_buttons()

    def _set_status(self, connected: bool, message: str) -> None:
        if connected:
            self.status_label.setText(f"Connected ({message})" if message else "Connected")
            self.status_label.setStyleSheet("color: #2e7d32;")
        else:
            text = message or "Disconnected"
            self.status_label.setText(text)
            self.status_label.setStyleSheet("color: #b03030;")

    def _update_buttons(self) -> None:
        connected = bool(self.terminal and self.terminal.is_connected)
        self.connect_button.setEnabled(not connected)
        self.disconnect_button.setEnabled(connected)

    def closeEvent(self, event: QtGui.QCloseEvent) -> None:  # pragma: no cover - GUI lifecycle
        self.shutdown()
        super().closeEvent(event)

    def shutdown(self) -> None:
        if hasattr(self, "_timer") and self._timer:
            self._timer.stop()
        if self.terminal:
            self.terminal.stop()
        root_logger = logging.getLogger()
        if self._log_handler in root_logger.handlers:
            root_logger.removeHandler(self._log_handler)
    def handle_add_subscription(self) -> None:
        topic = self.sub_topic_edit.text().strip()
        qos = self.sub_qos_spin.value()
        if not topic:
            self._show_error("Subscription topic cannot be empty.")
            return
        existing = next((sub for sub in self._subscriptions if sub.topic == topic), None)
        if existing:
            existing.qos = qos
        else:
            self._subscriptions.append(Subscription(topic, qos))
        self._refresh_subscription_table()
        self.sub_topic_edit.clear()
        if self.terminal and self.terminal.is_connected:
            try:
                self.terminal.subscribe(topic, qos)
            except Exception as exc:
                self._show_error(f"Failed to subscribe: {exc}")

    def handle_remove_subscription(self) -> None:
        current = self.subscription_table.currentRow()
        if current < 0:
            return
        topic_item = self.subscription_table.item(current, 0)
        if not topic_item:
            return
        topic = topic_item.text()
        self._subscriptions = [sub for sub in self._subscriptions if sub.topic != topic]
        self._refresh_subscription_table()
        if self.terminal and self.terminal.is_connected:
            try:
                self.terminal.unsubscribe(topic)
            except Exception as exc:
                self._show_error(f"Failed to unsubscribe: {exc}")

    def _refresh_subscription_table(self) -> None:
        self.subscription_table.setRowCount(0)
        for sub in self._subscriptions:
            row = self.subscription_table.rowCount()
            self.subscription_table.insertRow(row)
            self.subscription_table.setItem(row, 0, QtWidgets.QTableWidgetItem(sub.topic))
            self.subscription_table.setItem(row, 1, QtWidgets.QTableWidgetItem(str(sub.qos)))

    def _update_subscription_ack(self, payload: Dict[str, Any]) -> None:
        topic = payload.get("topic")
        qos = payload.get("qos")
        if not topic:
            return
        for sub in self._subscriptions:
            if sub.topic == topic and qos is not None:
                sub.qos = int(qos)
        self._refresh_subscription_table()

    def _remove_subscription_row(self, topic: Optional[str]) -> None:
        if not topic:
            return
        self._subscriptions = [sub for sub in self._subscriptions if sub.topic != topic]
        self._refresh_subscription_table()
    def handle_add_auto_publish(self) -> None:
        topic = self.auto_topic_edit.text().strip()
        payload = self.auto_payload_edit.text()
        qos = self.auto_qos_spin.value()
        retain = self.auto_retain_checkbox.isChecked()
        if not topic:
            self._show_error("Auto publish topic cannot be empty.")
            return
        existing = next((req for req in self._auto_publishes if req.topic == topic), None)
        if existing:
            existing.payload = payload
            existing.qos = qos
            existing.retain = retain
        else:
            self._auto_publishes.append(PublishRequest(topic, payload, qos, retain))
        self._refresh_auto_table()
        self.auto_topic_edit.clear()
        self.auto_payload_edit.clear()

    def handle_remove_auto_publish(self) -> None:
        current = self.auto_table.currentRow()
        if current < 0:
            return
        topic_item = self.auto_table.item(current, 0)
        if not topic_item:
            return
        topic = topic_item.text()
        self._auto_publishes = [req for req in self._auto_publishes if req.topic != topic]
        self._refresh_auto_table()

    def _refresh_auto_table(self) -> None:
        self.auto_table.setRowCount(0)
        for req in self._auto_publishes:
            row = self.auto_table.rowCount()
            self.auto_table.insertRow(row)
            self.auto_table.setItem(row, 0, QtWidgets.QTableWidgetItem(req.topic))
            self.auto_table.setItem(row, 1, QtWidgets.QTableWidgetItem(req.payload))
            self.auto_table.setItem(row, 2, QtWidgets.QTableWidgetItem(str(req.qos)))
            self.auto_table.setItem(row, 3, QtWidgets.QTableWidgetItem("Yes" if req.retain else "No"))
    def handle_publish(self) -> None:
        settings = self.collect_settings_from_ui()
        self.settings = settings
        if not self.terminal:
            self._show_error("MQTT client not initialised.")
            return
        self.terminal.settings = settings
        topic = self.pub_topic_edit.text().strip()
        payload = self.pub_payload_edit.toPlainText()
        if not topic:
            self._show_error("Publish topic cannot be empty.")
            return
        request = PublishRequest(topic, payload, self.pub_qos_spin.value(), self.pub_retain_checkbox.isChecked())
        count = self.pub_count_spin.value()
        interval = self.pub_interval_spin.value()

        def worker() -> None:
            try:
                for iteration in range(count):
                    self.terminal.publish(request)
                    if interval and iteration + 1 < count:
                        time.sleep(interval)
            except Exception as exc:
                self._event_queue.put(("error", {"message": f"Publish failed: {exc}"}))

        threading.Thread(target=worker, daemon=True).start()

    def handle_connect(self) -> None:
        if not self.terminal:
            self._create_terminal(self.collect_settings_from_ui())
        if self.terminal and self.terminal.is_connected:
            return
        settings = self.collect_settings_from_ui()
        self.settings = settings
        self._create_terminal(settings)
        timeout = self.timeout_spin.value()
        try:
            self.terminal.connect(timeout=timeout)
        except Exception as exc:
            self._show_error(f"Failed to connect: {exc}")
            logging.error("Connect failed: %s", exc)

    def handle_disconnect(self) -> None:
        if not self.terminal:
            return
        try:
            self.terminal.disconnect()
        except Exception as exc:
            self._show_error(f"Failed to disconnect: {exc}")

    def handle_auto_run(self) -> None:
        if not self.terminal:
            return
        settings = self.collect_settings_from_ui()
        self.settings = settings
        self.terminal.settings = settings
        count = max(1, self.auto_count_spin.value())
        interval = max(0.0, self.auto_interval_spin.value())
        wait_after = max(0.0, self.auto_wait_spin.value())

        def worker() -> None:
            try:
                self.terminal.run_auto_tests(count=count, interval=interval, wait_after=wait_after)
            except Exception as exc:
                self._event_queue.put(("error", {"message": f"Auto test failed: {exc}"}))

        threading.Thread(target=worker, daemon=True).start()
    def _add_message_row(self, record: Dict[str, Any]) -> None:
        timestamp = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime(record.get("timestamp", time.time())))
        topic = record.get("topic", "")
        payload_bytes = record.get("payload", b"")
        if isinstance(payload_bytes, bytes):
            preview = truncate_payload(payload_bytes)
        else:
            preview = str(payload_bytes)
        qos = record.get("qos", 0)
        retain = "Yes" if record.get("retain") else "No"
        row = self.messages_table.rowCount()
        self.messages_table.insertRow(row)
        for column, value in enumerate([timestamp, topic, preview, str(qos), retain]):
            self.messages_table.setItem(row, column, QtWidgets.QTableWidgetItem(value))
        limit = self.message_limit_spin.value()
        while self.messages_table.rowCount() > limit:
            self.messages_table.removeRow(0)

    def _append_log(self, message: str) -> None:
        self._log_buffer.append(message)
        if len(self._log_buffer) > self.LOG_LIMIT:
            self._log_buffer = self._log_buffer[-self.LOG_LIMIT :]
        self.log_view.setPlainText("\n".join(self._log_buffer))
        self.log_view.verticalScrollBar().setValue(self.log_view.verticalScrollBar().maximum())

    def _clear_log(self) -> None:
        self._log_buffer.clear()
        self.log_view.clear()

    def _format_log_payload(self, payload: Dict[str, Any]) -> str:
        timestamp = time.strftime("%H:%M:%S", time.localtime(payload.get("timestamp", time.time())))
        return f"[{timestamp}] {payload.get('level', 'INFO')}: {payload.get('message', '')}"

    def _show_error(self, message: str) -> None:
        QtWidgets.QMessageBox.critical(self, "MQTT", message)
        self._append_log(f"ERROR: {message}")

    def _on_log_level_changed(self, level_name: str) -> None:
        level = logging.getLevelName(level_name.upper())
        if isinstance(level, str):
            return
        logging.getLogger().setLevel(level)
        self._append_log(f"Log level set to {level_name.upper()}")
    def _apply_settings_to_ui(self, settings: Dict[str, Any]) -> None:
        connection = settings.get("connection", {})
        self.host_edit.setText(str(connection.get("host", "localhost")))
        self.port_spin.setValue(int(connection.get("port", 1883)))
        self.client_id_edit.setText(str(connection.get("client_id", "")))
        self.keepalive_spin.setValue(int(connection.get("keepalive", 60)))
        self.protocol_combo.setCurrentText(str(connection.get("protocol", "3.1.1")))
        self.transport_combo.setCurrentText(str(connection.get("transport", "tcp")))
        self.clean_session_checkbox.setChecked(bool(connection.get("clean_session", True)))
        self.message_limit_spin.setValue(int(settings.get("message_log_limit", 100)))

        auth = settings.get("auth", {})
        self.username_edit.setText(str(auth.get("username")) if auth.get("username") else "")
        self.password_edit.setText(str(auth.get("password")) if auth.get("password") else "")
        tls_cfg = auth.get("tls", {})
        self.tls_checkbox.setChecked(bool(tls_cfg.get("enabled")))
        self.ca_path_edit.setText(str(tls_cfg.get("ca_certs")) if tls_cfg.get("ca_certs") else "")
        self.cert_path_edit.setText(str(tls_cfg.get("certfile")) if tls_cfg.get("certfile") else "")
        self.key_path_edit.setText(str(tls_cfg.get("keyfile")) if tls_cfg.get("keyfile") else "")
        self.tls_version_combo.setCurrentText(str(tls_cfg.get("tls_version", "SYSTEM_DEFAULT")))
        self.ciphers_edit.setText(str(tls_cfg.get("ciphers")) if tls_cfg.get("ciphers") else "")
        self.insecure_checkbox.setChecked(bool(tls_cfg.get("insecure", False)))
        self._toggle_tls_inputs(self.tls_checkbox.isChecked())

        last_will = settings.get("last_will", {})
        self.will_topic_edit.setText(str(last_will.get("topic")) if last_will.get("topic") else "")
        self.will_payload_edit.setText(str(last_will.get("payload", "")))
        self.will_qos_spin.setValue(int(last_will.get("qos", 0)))
        self.will_retain_checkbox.setChecked(bool(last_will.get("retain", False)))

        log_level = settings.get("log_level", "INFO").upper()
        index = self.log_level_combo.findText(log_level)
        if index >= 0:
            self.log_level_combo.setCurrentIndex(index)

        auto_cfg = settings.get("auto_test", {})
        self.auto_enabled_checkbox.setChecked(bool(auto_cfg.get("enabled", False)))
        self.auto_count_spin.setValue(int(auto_cfg.get("count", 1)))
        self.auto_interval_spin.setValue(float(auto_cfg.get("interval", 1.0)))
        self.auto_wait_spin.setValue(float(auto_cfg.get("wait_after", 2.0)))

        self.auto_connect_checkbox.setChecked(bool(settings.get("auto_connect", True)))

    def collect_settings_from_ui(self) -> Dict[str, Any]:
        connection = {
            "host": self.host_edit.text().strip() or "localhost",
            "port": self.port_spin.value(),
            "client_id": self.client_id_edit.text().strip(),
            "keepalive": self.keepalive_spin.value(),
            "clean_session": self.clean_session_checkbox.isChecked(),
            "protocol": self.protocol_combo.currentText(),
            "transport": self.transport_combo.currentText(),
            "reconnect_delay_min": self.settings.get("connection", {}).get("reconnect_delay_min", 1),
            "reconnect_delay_max": self.settings.get("connection", {}).get("reconnect_delay_max", 120),
            "reconnect_exponential_backoff": self.settings.get("connection", {}).get("reconnect_exponential_backoff", False),
        }
        auth = {
            "username": self.username_edit.text().strip() or None,
            "password": self.password_edit.text() or None,
            "tls": {
                "enabled": self.tls_checkbox.isChecked(),
                "ca_certs": self.ca_path_edit.text().strip() or None,
                "certfile": self.cert_path_edit.text().strip() or None,
                "keyfile": self.key_path_edit.text().strip() or None,
                "tls_version": self.tls_version_combo.currentText(),
                "ciphers": self.ciphers_edit.text().strip() or None,
                "insecure": self.insecure_checkbox.isChecked(),
            },
        }
        last_will = {
            "topic": self.will_topic_edit.text().strip() or None,
            "payload": self.will_payload_edit.text(),
            "qos": self.will_qos_spin.value(),
            "retain": self.will_retain_checkbox.isChecked(),
        }
        auto_cfg = {
            "enabled": self.auto_enabled_checkbox.isChecked(),
            "count": self.auto_count_spin.value(),
            "interval": self.auto_interval_spin.value(),
            "wait_after": self.auto_wait_spin.value(),
        }
        config = {
            "connection": connection,
            "auth": auth,
            "last_will": last_will,
            "subscriptions": [Subscription(sub.topic, sub.qos) for sub in self._subscriptions],
            "publishes": [PublishRequest(req.topic, req.payload, req.qos, req.retain) for req in self._auto_publishes],
            "auto_test": auto_cfg,
            "auto_connect": self.auto_connect_checkbox.isChecked(),
            "message_log_limit": self.message_limit_spin.value(),
            "log_level": self.log_level_combo.currentText(),
        }
        return config
def parse_args(argv: Optional[Sequence[str]] = None) -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Delta X Software MQTT tester GUI")
    parser.add_argument("--config", help="Path to JSON configuration file.")
    parser.add_argument("--host", help="MQTT broker host.")
    parser.add_argument("--port", type=int, help="MQTT broker port.")
    parser.add_argument("--client-id", help="MQTT client identifier.")
    parser.add_argument("--username", help="Username for authentication.")
    parser.add_argument("--password", help="Password for authentication.")
    parser.add_argument("--keepalive", type=int, help="Keepalive interval in seconds.")
    parser.add_argument(
        "--clean-session",
        dest="clean_session",
        action=argparse.BooleanOptionalAction,
        help="Enable or disable clean session flag (MQTT 3.x only).",
    )
    parser.add_argument("--protocol", choices=sorted(PROTOCOL_MAP.keys()), help="MQTT protocol version.")
    parser.add_argument("--transport", choices=["tcp", "websockets"], help="Transport protocol.")
    parser.add_argument("--reconnect-delay-min", type=int, help="Minimum reconnect delay.")
    parser.add_argument("--reconnect-delay-max", type=int, help="Maximum reconnect delay.")
    parser.add_argument(
        "--reconnect-exponential-backoff",
        dest="reconnect_exponential_backoff",
        action=argparse.BooleanOptionalAction,
        help="Use exponential backoff for reconnect attempts (if supported).",
    )
    parser.add_argument("--tls", dest="tls", action=argparse.BooleanOptionalAction, help="Enable TLS connection.")
    parser.add_argument("--ca-certs", dest="ca_certs", help="Path to CA certificate file.")
    parser.add_argument("--certfile", help="Path to client certificate file.")
    parser.add_argument("--keyfile", help="Path to client private key file.")
    parser.add_argument(
        "--tls-version",
        dest="tls_version",
        choices=sorted(TLS_VERSION_MAP.keys()),
        help="TLS protocol version.",
    )
    parser.add_argument("--ciphers", help="Cipher string for TLS connections.")
    parser.add_argument(
        "--insecure",
        dest="insecure",
        action=argparse.BooleanOptionalAction,
        help="Disable TLS certificate validation (not recommended).",
    )
    parser.add_argument("--will-topic", help="Last will topic.")
    parser.add_argument("--will-payload", help="Last will payload.")
    parser.add_argument("--will-qos", type=int, help="Last will QoS.")
    parser.add_argument(
        "--will-retain",
        dest="will_retain",
        action=argparse.BooleanOptionalAction,
        help="Retain the last will message.",
    )
    parser.add_argument("--subscribe", action="append", help="Subscribe descriptor 'topic::qos'. Repeatable.")
    parser.add_argument(
        "--publish",
        action="append",
        help="Publish descriptor 'topic::payload[::qos[::retain]]'. Repeatable.",
    )
    parser.add_argument("--auto", dest="auto", action=argparse.BooleanOptionalAction, help="Enable automatic publish-run mode.")
    parser.add_argument("--auto-count", type=int, help="Number of auto publish iterations.")
    parser.add_argument("--auto-interval", type=float, help="Delay between auto publish iterations.")
    parser.add_argument("--auto-wait", type=float, help="Wait after auto publish before exiting.")
    parser.add_argument(
        "--auto-connect",
        dest="auto_connect",
        action=argparse.BooleanOptionalAction,
        help="Automatically connect on startup.",
    )
    parser.add_argument(
        "--message-log-limit",
        type=int,
        help="Number of recent messages to retain for inspection.",
    )
    parser.add_argument("--log-level", help="Logging level (DEBUG, INFO, WARNING, ERROR, CRITICAL).")
    parser.add_argument("--quiet", action="store_true", help="Reduce log noise (equivalent to WARNING level).")
    parser.add_argument("--timeout", type=float, default=15.0, help="Connection timeout in seconds when auto-connecting.")
    parser.add_argument("--no-connect", action="store_true", help="Do not connect automatically, even if auto-connect is enabled.")
    return parser.parse_args(argv)


def build_settings(args: argparse.Namespace) -> Dict[str, Any]:
    config = deep_merge(DEFAULT_CONFIG, load_config(args.config))
    config = apply_cli_overrides(config, args)
    return normalise_settings(config)


def main(argv: Optional[Sequence[str]] = None) -> int:
    args = parse_args(argv)
    try:
        setup_logging(args.log_level or DEFAULT_CONFIG.get("log_level"), args.quiet)
    except ValueError as exc:
        print(f"Error: {exc}")
        return 2
    try:
        settings = build_settings(args)
    except (ValueError, FileNotFoundError) as exc:
        logging.error(str(exc))
        settings = normalise_settings(deepcopy(DEFAULT_CONFIG))

    app = QtWidgets.QApplication(sys.argv if argv is None else list(argv))
    window = MQTTMainWindow(settings, no_connect=args.no_connect, timeout=args.timeout)
    app.aboutToQuit.connect(window.shutdown)
    window.show()
    return app.exec_()


if __name__ == "__main__":  # pragma: no cover - GUI entry point
    sys.exit(main())
