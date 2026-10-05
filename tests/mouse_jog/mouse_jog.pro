QT += core gui widgets testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_mouse_jog
INCLUDEPATH += $$PWD/../../include
SOURCES += $$PWD/tst_mouse_jog.cpp \
    $$PWD/../../src/MouseJogController.cpp \
    $$PWD/../../src/MouseJogDialog.cpp \
    $$PWD/../../src/RelativeMouseCapture.cpp \
    $$PWD/../../src/GcodeMotionPlanner.cpp \
    $$PWD/../../src/LiveTargetTracker.cpp \
    $$PWD/../../src/GcodeMotionStream.cpp \
    $$PWD/../../src/DeviceCommandBroker.cpp
HEADERS += $$PWD/../../include/MouseJogController.h \
    $$PWD/../../include/MouseJogDialog.h \
    $$PWD/../../include/RelativeMouseCapture.h \
    $$PWD/../../include/GcodeMotionPlanner.h \
    $$PWD/../../include/LiveTargetTracker.h \
    $$PWD/../../include/GcodeMotionStream.h \
    $$PWD/../../include/DeviceCommandBroker.h
win32:msvc*: QMAKE_CXXFLAGS += /Zc:__cplusplus /permissive-
win32:LIBS += -luser32
