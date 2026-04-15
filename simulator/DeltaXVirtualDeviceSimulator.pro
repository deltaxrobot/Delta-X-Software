QT += core gui widgets network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

macx {
    QMAKE_CFLAGS += -include arm_acle.h
    QMAKE_CXXFLAGS += -include arm_acle.h
    QMAKE_INFO_PLIST = $$PWD/resources/macos/Info.plist
}

TARGET = DeltaXVirtualDeviceSimulator
TEMPLATE = app

INCLUDEPATH += $$PWD/src \
               $$PWD/../include
DEPENDPATH += $$INCLUDEPATH

SOURCES += \
    $$PWD/src/main.cpp \
    $$PWD/src/DeviceSimulatorWindow.cpp \
    $$PWD/src/VirtualSerialPort.cpp \
    $$PWD/src/VirtualDeviceServer.cpp

HEADERS += \
    $$PWD/src/DeviceSimulatorWindow.h \
    $$PWD/src/VirtualSerialPort.h \
    $$PWD/src/VirtualDeviceServer.h
