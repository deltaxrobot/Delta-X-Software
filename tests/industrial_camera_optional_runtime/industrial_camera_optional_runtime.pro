QT += core gui widgets testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_industrial_camera_optional_runtime

INCLUDEPATH += \
    $$PWD/../../sdk

DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)

SOURCES += tst_industrial_camera_optional_runtime.cpp
HEADERS += $$PWD/../../sdk/DeltaXPlugin.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
