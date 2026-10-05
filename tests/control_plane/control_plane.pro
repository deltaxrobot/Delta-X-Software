QT += core testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_control_plane

INCLUDEPATH += $$PWD/../../include

SOURCES += \
    $$PWD/tst_control_plane.cpp \
    $$PWD/../../src/DeviceCommandBroker.cpp \
    $$PWD/../../src/CellSupervisor.cpp

HEADERS += \
    $$PWD/../../include/DeviceCommandBroker.h \
    $$PWD/../../include/CellSupervisor.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus /permissive-
}
