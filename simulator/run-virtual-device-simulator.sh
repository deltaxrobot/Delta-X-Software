#!/bin/sh
set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
QT_DIR="${HOME}/Qt/6.10.1/macos"
APP_BIN="${ROOT_DIR}/build/DeltaXVirtualDeviceSimulator.app/Contents/MacOS/DeltaXVirtualDeviceSimulator"
LEGACY_BIN="${ROOT_DIR}/build/DeltaXVirtualDeviceSimulator"

if [ ! -x "${APP_BIN}" ]; then
    APP_BIN="${LEGACY_BIN}"
fi

if [ ! -x "${APP_BIN}" ]; then
    echo "Simulator binary not found at ${ROOT_DIR}/build" >&2
    echo "Build it first:" >&2
    echo "  mkdir -p ${ROOT_DIR}/build && cd ${ROOT_DIR}/build" >&2
    echo "  \"${QT_DIR}/bin/qmake\" ../DeltaXVirtualDeviceSimulator.pro && make -j\"$(sysctl -n hw.ncpu)\"" >&2
    exit 1
fi

export QT_PLUGIN_PATH="${QT_DIR}/plugins"

exec "${APP_BIN}" "$@"
