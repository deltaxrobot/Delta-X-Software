QT += core gui widgets network testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_socket_vision_protocol

INCLUDEPATH += \
    $$PWD/../../include

DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)

SOURCES += \
    $$PWD/tst_socket_vision_protocol.cpp \
    $$PWD/../tracking_claim/UnityTool_stub.cpp \
    $$PWD/../../src/SocketConnectionManager.cpp \
    $$PWD/../../src/VariableManager.cpp

HEADERS += \
    $$PWD/../../include/ObjectInfo.h \
    $$PWD/../../include/SocketConnectionManager.h \
    $$PWD/../../include/VariableManager.h \
    $$PWD/../../include/VisionDetections.h \
    $$PWD/../../include/VisionTypes.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
