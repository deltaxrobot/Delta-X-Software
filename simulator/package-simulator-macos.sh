#!/bin/sh
set -eu

ROOT_DIR="$(CDPATH= cd -- "$(dirname "$0")" && pwd)"
BUILD_DIR="${ROOT_DIR}/build"
QT_DIR="${HOME}/Qt/6.10.1/macos"
APP_BUNDLE="${BUILD_DIR}/DeltaXVirtualDeviceSimulator.app"

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"

"${QT_DIR}/bin/qmake" ../DeltaXVirtualDeviceSimulator.pro
make -j"$(sysctl -n hw.ncpu)"

"${QT_DIR}/bin/macdeployqt" "${APP_BUNDLE}"
codesign --force --deep -s - "${APP_BUNDLE}"

echo "Packaged app bundle:"
echo "  ${APP_BUNDLE}"
