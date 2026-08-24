QT += core network serialport testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_device_state

INCLUDEPATH += \
    $$PWD/../../include \
    $$PWD/../../include/device

SOURCES += \
    $$PWD/tst_device_state.cpp \
    $$PWD/../../src/device/device.cpp \
    $$PWD/../../src/device/encoder.cpp \
    $$PWD/../../src/device/conveyor.cpp

HEADERS += \
    $$PWD/../../include/device/device.h \
    $$PWD/../../include/device/encoder.h \
    $$PWD/../../include/device/conveyor.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
