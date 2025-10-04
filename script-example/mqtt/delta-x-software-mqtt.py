# mqtt_gcode_bridge.py
import json, time, uuid, threading, queue
from typing import List, Optional
import paho.mqtt.client as mqtt
import serial
import serial.tools.list_ports
import tkinter as tk
from tkinter import ttk, scrolledtext, messagebox
from datetime import datetime

# ====== CONFIGURATION - MODIFY AS NEEDED ======
MQTT_HOST   = "maxbyte.crystalmq.com"
MQTT_PORT   = 1883            # if broker requires TLS: use 8883 + tls_set(...)
MQTT_USER   = "PUB_SKM"
MQTT_PASS   = "PUB_SKM"
MQTT_TOPIC  = "SREC_Delta_XS_Robot"

SERIAL_PORT = "COM5"          # example: Windows: "COM3"; Linux: "/dev/ttyUSB0"
SERIAL_BAUD = 115200
SERIAL_TIMEOUT_S = 2.0        # wait for robot response per line
# =============================================

# Map standardized commands → G-code (adjust according to your firmware)
STD2GCODE = {
    "home": ["G28"],          # home position
    "position": ["Position"], # position query (depends on firmware)
}

q_cmd = queue.Queue()         # command queue (cmd JSON)
busy_lock = threading.Lock()
is_busy = False
serial_connected = False  # serial port connection status
serial_port_selected = SERIAL_PORT  # currently selected serial port
serial_instance = None  # global serial instance
gui_log = None  # GUI log widget reference

# --- Serial helpers ---
def log_message(msg: str, level: str = "INFO"):
    """Log message to console and GUI"""
    timestamp = datetime.now().strftime("%H:%M:%S")
    log_line = f"[{timestamp}] [{level}] {msg}"
    print(log_line)
    if gui_log:
        gui_log.insert(tk.END, log_line + "\n")
        gui_log.see(tk.END)

def get_available_ports():
    """Get list of available COM ports"""
    ports = serial.tools.list_ports.comports()
    return [port.device for port in ports]

def open_serial() -> serial.Serial:
    global serial_connected, serial_instance
    ser = serial.Serial(serial_port_selected, SERIAL_BAUD, timeout=SERIAL_TIMEOUT_S)
    # If need to "wake up" controller:
    time.sleep(0.5)
    serial_connected = True
    serial_instance = ser
    log_message(f"Serial port {serial_port_selected} opened successfully")
    return ser

def close_serial():
    """Close serial connection"""
    global serial_connected, serial_instance
    if serial_instance and serial_instance.is_open:
        try:
            serial_instance.close()
            serial_connected = False
            serial_instance = None
            log_message("Serial port closed")
            return True
        except Exception as e:
            log_message(f"Error closing serial: {e}", "ERROR")
            return False
    else:
        log_message("Serial port already closed", "WARN")
        return True

def send_gcode_line(ser: serial.Serial, line: str) -> str:
    ln = (line.strip() + "\n").encode("ascii")
    ser.write(ln)
    ser.flush()
    log_message(f"Sent: {line.strip()}", "GCODE")
    # Read until 'ok' or 'error' / timeout
    t0 = time.time()
    buff = []
    while time.time() - t0 < SERIAL_TIMEOUT_S:
        rx = ser.readline().decode(errors="ignore").strip()
        if not rx:
            continue
        buff.append(rx)
        # simple: if see "ok" consider done
        if "ok" in rx.lower():
            log_message(f"Response: {rx}", "GCODE")
            return "ok"
        if "error" in rx.lower() or "alarm" in rx.lower():
            log_message(f"Error: {' | '.join(buff)}", "ERROR")
            return "error: " + " | ".join(buff)
    log_message(f"Timeout: {' | '.join(buff)}", "WARN")
    return "timeout: " + " | ".join(buff)

def run_program(ser: serial.Serial, lines: List[str], ack_cb) -> Optional[str]:
    """
    Send multiple G-code lines; returns None if ok, or string describing error.
    """
    for idx, line in enumerate(lines, start=1):
        if not line.strip():
            continue
        r = send_gcode_line(ser, line)
        if r != "ok":
            return f"line {idx}: {r}"
    return None

# --- MQTT side ---
client = mqtt.Client(client_id=f"dxs-bridge-{uuid.uuid4()}", clean_session=True)
client.username_pw_set(MQTT_USER, MQTT_PASS)
# If broker requires TLS:
# client.tls_set()  # add CA/Cert if needed
# MQTT keepalive
KEEPALIVE = 30

def publish_ack(cmd_id: str, status: str, msg: str, data: dict | None = None):
    payload = {"dir":"ack","cmd_id":cmd_id,"status":status,"msg":msg}
    if data: payload["data"] = data
    client.publish(MQTT_TOPIC, json.dumps(payload), qos=1, retain=False)
    log_message(f"Published ACK: {status} - {msg}", "MQTT")

def on_connect(c, u, f, rc):
    log_message(f"MQTT connected with result code: {rc}", "MQTT")
    c.subscribe(MQTT_TOPIC, qos=1)
    log_message(f"Subscribed to topic: {MQTT_TOPIC}", "MQTT")

def on_message(c, u, msg):
    global is_busy
    try:
        data = json.loads(msg.payload.decode("utf-8"))
        # Ignore our own ack messages
        if data.get("dir") != "cmd":
            return
        log_message(f"Received command: {data.get('type', 'unknown')}", "MQTT")
        # If busy, reject new command (or you can queue it)
        with busy_lock:
            if is_busy and q_cmd.qsize() > 0:
                publish_ack(data.get("cmd_id","na"), "rejected", "Busy")
                return
            q_cmd.put(data)
    except Exception as e:
        log_message(f"on_message error: {e}", "ERROR")

client.on_connect = on_connect
client.on_message = on_message

def worker():
    global is_busy, serial_connected, serial_instance
    while True:
        cmd = q_cmd.get()
        with busy_lock:
            is_busy = True
        cmd_id = cmd.get("cmd_id") or str(uuid.uuid4())
        typ    = cmd.get("type")
        t0 = time.time()

        try:
            # Lazy-open serial (if cable disconnected during runtime)
            if (serial_instance is None) or (not serial_instance.is_open):
                serial_instance = open_serial()

            # Determine G-code line list
            if typ == "gcode":
                prog = [cmd.get("gcode","")]
            elif typ == "program":
                prog = cmd.get("program", [])
            elif typ in STD2GCODE:
                prog = STD2GCODE[typ]
            else:
                publish_ack(cmd_id, "error", f"Unknown type: {typ}")
                with busy_lock: is_busy = False
                continue

            # Execute
            log_message(f"Executing command: {typ}", "WORKER")
            err = run_program(serial_instance, prog, publish_ack)
            elapsed = int((time.time()-t0)*1000)

            if err is None:
                publish_ack(cmd_id, "ok", "ok", {"elapsed_ms": elapsed})
                log_message(f"Command completed in {elapsed}ms", "WORKER")
            else:
                publish_ack(cmd_id, "error", err)
                log_message(f"Command failed: {err}", "ERROR")
        except Exception as e:
            publish_ack(cmd_id, "error", f"Exception: {e}")
            log_message(f"Worker exception: {e}", "ERROR")
            # try to close serial for next attempt
            serial_connected = False
            try:
                if serial_instance and serial_instance.is_open: 
                    serial_instance.close()
            except: pass
            serial_instance = None
        finally:
            with busy_lock:
                is_busy = False
        q_cmd.task_done()

# --- GUI Interface ---
class MQTTBridgeGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("MQTT-Serial G-code Bridge")
        self.root.geometry("900x700")
        
        # Configure style
        style = ttk.Style()
        style.configure("Status.TLabel", font=("Arial", 10))
        
        # Top frame - Status indicators
        status_frame = ttk.LabelFrame(root, text="Connection Status", padding=10)
        status_frame.pack(fill=tk.X, padx=10, pady=5)
        
        # MQTT Status
        ttk.Label(status_frame, text="MQTT:").grid(row=0, column=0, sticky=tk.W, padx=5)
        self.mqtt_status = ttk.Label(status_frame, text="Disconnected", 
                                      style="Status.TLabel", foreground="red")
        self.mqtt_status.grid(row=0, column=1, sticky=tk.W, padx=5)
        
        # Serial Status
        ttk.Label(status_frame, text="Serial:").grid(row=0, column=2, sticky=tk.W, padx=5)
        self.serial_status = ttk.Label(status_frame, text="Not Opened", 
                                        style="Status.TLabel", foreground="orange")
        self.serial_status.grid(row=0, column=3, sticky=tk.W, padx=5)
        
        # Busy Status
        ttk.Label(status_frame, text="Status:").grid(row=0, column=4, sticky=tk.W, padx=5)
        self.busy_status = ttk.Label(status_frame, text="Idle", 
                                      style="Status.TLabel", foreground="green")
        self.busy_status.grid(row=0, column=5, sticky=tk.W, padx=5)
        
        # Config info frame
        config_frame = ttk.LabelFrame(root, text="Configuration", padding=10)
        config_frame.pack(fill=tk.X, padx=10, pady=5)
        
        # MQTT Config
        mqtt_text = f"MQTT: {MQTT_HOST}:{MQTT_PORT} | Topic: {MQTT_TOPIC}"
        ttk.Label(config_frame, text=mqtt_text, font=("Courier", 9)).pack(anchor=tk.W)
        
        # Serial Config with port selection
        serial_config_frame = ttk.Frame(config_frame)
        serial_config_frame.pack(fill=tk.X, pady=5)
        
        ttk.Label(serial_config_frame, text="Serial Port:", font=("Arial", 9)).pack(side=tk.LEFT, padx=5)
        
        # COM port selection
        self.port_combo = ttk.Combobox(serial_config_frame, width=15, state="readonly")
        self.port_combo.pack(side=tk.LEFT, padx=5)
        self.refresh_ports()
        self.port_combo.bind('<<ComboboxSelected>>', self.on_port_selected)
        
        # Refresh button
        ttk.Button(serial_config_frame, text="Refresh", 
                   command=self.refresh_ports, width=8).pack(side=tk.LEFT, padx=5)
        
        # Connect/Disconnect button
        self.connect_btn = ttk.Button(serial_config_frame, text="Connect", 
                                       command=self.toggle_serial_connection, width=10)
        self.connect_btn.pack(side=tk.LEFT, padx=5)
        
        ttk.Label(serial_config_frame, text=f"@ {SERIAL_BAUD} baud", 
                  font=("Courier", 9)).pack(side=tk.LEFT, padx=5)
        
        # Manual command frame
        cmd_frame = ttk.LabelFrame(root, text="Manual Command", padding=10)
        cmd_frame.pack(fill=tk.X, padx=10, pady=5)
        
        ttk.Label(cmd_frame, text="G-code:").grid(row=0, column=0, sticky=tk.W, padx=5)
        self.gcode_entry = ttk.Entry(cmd_frame, width=50)
        self.gcode_entry.grid(row=0, column=1, padx=5)
        self.gcode_entry.bind('<Return>', lambda e: self.send_manual_command())
        
        self.send_btn = ttk.Button(cmd_frame, text="Send", command=self.send_manual_command)
        self.send_btn.grid(row=0, column=2, padx=5)
        
        # Quick commands
        quick_frame = ttk.Frame(cmd_frame)
        quick_frame.grid(row=1, column=0, columnspan=3, pady=5)
        
        ttk.Button(quick_frame, text="Home (G28)", 
                   command=lambda: self.send_quick_cmd("home")).pack(side=tk.LEFT, padx=5)
        ttk.Button(quick_frame, text="Position", 
                   command=lambda: self.send_quick_cmd("position")).pack(side=tk.LEFT, padx=5)
        
        # Log frame
        log_frame = ttk.LabelFrame(root, text="Activity Log", padding=10)
        log_frame.pack(fill=tk.BOTH, expand=True, padx=10, pady=5)
        
        # Create scrolled text widget for logs
        self.log_text = scrolledtext.ScrolledText(log_frame, wrap=tk.WORD, 
                                                    height=20, font=("Courier", 9))
        self.log_text.pack(fill=tk.BOTH, expand=True)
        
        # Set global log reference
        global gui_log
        gui_log = self.log_text
        
        # Button frame
        btn_frame = ttk.Frame(root)
        btn_frame.pack(fill=tk.X, padx=10, pady=5)
        
        ttk.Button(btn_frame, text="Clear Log", 
                   command=self.clear_log).pack(side=tk.LEFT, padx=5)
        ttk.Button(btn_frame, text="Exit", 
                   command=self.on_closing).pack(side=tk.RIGHT, padx=5)
        
        # Start status update loop
        self.update_status()
        
        # Handle window close
        self.root.protocol("WM_DELETE_WINDOW", self.on_closing)
        
        log_message("GUI initialized", "GUI")
    
    def refresh_ports(self):
        """Refresh the list of available COM ports"""
        ports = get_available_ports()
        self.port_combo['values'] = ports
        if ports:
            # Try to select the default port or previously selected port
            global serial_port_selected
            if serial_port_selected in ports:
                self.port_combo.set(serial_port_selected)
            else:
                self.port_combo.current(0)
                serial_port_selected = ports[0]
        else:
            self.port_combo.set("No ports found")
        log_message(f"Found {len(ports)} serial ports", "GUI")
    
    def on_port_selected(self, event):
        """Handle port selection change"""
        global serial_port_selected
        selected = self.port_combo.get()
        if selected and selected != "No ports found":
            serial_port_selected = selected
            log_message(f"Selected port: {serial_port_selected}", "GUI")
    
    def toggle_serial_connection(self):
        """Connect or disconnect serial port"""
        global serial_connected
        
        if serial_connected:
            # Disconnect
            if close_serial():
                self.connect_btn.config(text="Connect")
                self.port_combo.config(state="readonly")
                messagebox.showinfo("Success", "Serial port disconnected")
        else:
            # Connect
            try:
                open_serial()
                self.connect_btn.config(text="Disconnect")
                self.port_combo.config(state="disabled")
                messagebox.showinfo("Success", f"Connected to {serial_port_selected}")
            except Exception as e:
                messagebox.showerror("Connection Error", f"Failed to open port:\n{e}")
                log_message(f"Failed to open port: {e}", "ERROR")
    
    def send_manual_command(self):
        if not serial_connected:
            messagebox.showwarning("Not Connected", "Please connect to serial port first")
            return
            
        gcode = self.gcode_entry.get().strip()
        if not gcode:
            return
        
        cmd = {
            "dir": "cmd",
            "cmd_id": str(uuid.uuid4()),
            "type": "gcode",
            "gcode": gcode
        }
        q_cmd.put(cmd)
        log_message(f"Manual command queued: {gcode}", "GUI")
        self.gcode_entry.delete(0, tk.END)
    
    def send_quick_cmd(self, cmd_type: str):
        if not serial_connected:
            messagebox.showwarning("Not Connected", "Please connect to serial port first")
            return
            
        cmd = {
            "dir": "cmd",
            "cmd_id": str(uuid.uuid4()),
            "type": cmd_type
        }
        q_cmd.put(cmd)
        log_message(f"Quick command queued: {cmd_type}", "GUI")
    
    def update_status(self):
        # Update MQTT status
        if client.is_connected():
            self.mqtt_status.config(text="Connected", foreground="green")
        else:
            self.mqtt_status.config(text="Disconnected", foreground="red")
        
        # Update Serial status and button
        if serial_connected:
            self.serial_status.config(text=f"Connected ({serial_port_selected})", foreground="green")
            self.connect_btn.config(text="Disconnect")
            self.port_combo.config(state="disabled")
        else:
            self.serial_status.config(text="Not Connected", foreground="orange")
            self.connect_btn.config(text="Connect")
            self.port_combo.config(state="readonly")
        
        # Update busy status
        with busy_lock:
            if is_busy:
                self.busy_status.config(text="Busy", foreground="red")
            else:
                self.busy_status.config(text="Idle", foreground="green")
        
        # Schedule next update
        self.root.after(500, self.update_status)
    
    def clear_log(self):
        self.log_text.delete(1.0, tk.END)
        log_message("Log cleared", "GUI")
    
    def on_closing(self):
        log_message("Shutting down...", "GUI")
        # Close serial connection before exit
        if serial_connected:
            close_serial()
        self.root.quit()

def main():
    # Start worker thread
    threading.Thread(target=worker, daemon=True).start()
    
    # Start MQTT in separate thread
    def mqtt_thread():
        try:
            client.connect(MQTT_HOST, MQTT_PORT, keepalive=KEEPALIVE)
            client.loop_forever()
        except Exception as e:
            log_message(f"MQTT connection error: {e}", "ERROR")
    
    threading.Thread(target=mqtt_thread, daemon=True).start()
    
    # Create and run GUI
    root = tk.Tk()
    gui = MQTTBridgeGUI(root)
    
    log_message("Application started", "MAIN")
    log_message(f"Connecting to MQTT broker: {MQTT_HOST}:{MQTT_PORT}", "MAIN")
    
    root.mainloop()

if __name__ == "__main__":
    main()
