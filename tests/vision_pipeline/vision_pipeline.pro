QT += core gui widgets testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_vision_pipeline

INCLUDEPATH += \
    $$PWD/../../include

DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)

SOURCES += \
    $$PWD/tst_vision_pipeline.cpp \
    $$PWD/../../src/CalibrationMath.cpp \
    $$PWD/../../src/TaskNode.cpp

HEADERS += \
    $$PWD/../../include/CalibrationMath.h \
    $$PWD/../../include/TaskNode.h \
    $$PWD/../../include/VisionTypes.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
