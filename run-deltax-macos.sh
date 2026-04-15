#!/bin/sh
set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
QT_DIR="${HOME}/Qt/6.10.1/macos"
APP_BUNDLE="${ROOT_DIR}/build/macos-qt6-release/DeltaRobotSoftware.app"
APP_BIN="${ROOT_DIR}/build/macos-qt6-release/DeltaRobotSoftware.app/Contents/MacOS/DeltaRobotSoftware"
LOG_DIR="${ROOT_DIR}/logs"
TIMESTAMP="$(date +"%Y%m%d-%H%M%S")"
LOG_FILE="${LOG_DIR}/deltax-runtime-${TIMESTAMP}.log"
LATEST_LOG="${LOG_DIR}/deltax-runtime-latest.log"

if [ ! -d "${APP_BUNDLE}" ] || [ ! -x "${APP_BIN}" ]; then
    echo "DeltaRobotSoftware app bundle not found at ${APP_BUNDLE}" >&2
    exit 1
fi

mkdir -p "${LOG_DIR}"
ln -sf "${LOG_FILE}" "${LATEST_LOG}"
export QT_PLUGIN_PATH="${QT_DIR}/plugins"

{
    echo "[$(date +"%Y-%m-%d %H:%M:%S")] Starting DeltaRobotSoftware"
    echo "APP_BUNDLE=${APP_BUNDLE}"
    echo "APP_BIN=${APP_BIN}"
    echo "QT_PLUGIN_PATH=${QT_PLUGIN_PATH}"
    open -n "${APP_BUNDLE}"
    sleep 2
    APP_PID="$(pgrep -nf "${APP_BIN}" || true)"
    if [ -n "${APP_PID}" ]; then
        echo "[$(date +"%Y-%m-%d %H:%M:%S")] DeltaRobotSoftware launched with PID ${APP_PID}"
        (
            while kill -0 "${APP_PID}" 2>/dev/null; do
                sleep 1
            done
            {
                echo "[$(date +"%Y-%m-%d %H:%M:%S")] DeltaRobotSoftware process ${APP_PID} terminated"
                if [ -f "${ROOT_DIR}/mylog.txt" ]; then
                    echo "----- mylog tail -----"
                    tail -n 200 "${ROOT_DIR}/mylog.txt"
                    echo "----- end mylog tail -----"
                fi
            } >>"${LOG_FILE}" 2>&1
        ) &
    else
        echo "[$(date +"%Y-%m-%d %H:%M:%S")] Failed to detect DeltaRobotSoftware PID after launch"
        exit 1
    fi
} >>"${LOG_FILE}" 2>&1
