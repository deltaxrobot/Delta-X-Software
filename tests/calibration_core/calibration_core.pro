QT += core gui widgets testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_calibration_core

INCLUDEPATH += \
    $$PWD/../../include

DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)

SOURCES += \
    $$PWD/tst_calibration_core.cpp \
    $$PWD/../variable_manager/UnityTool_stub.cpp \
    $$PWD/../../src/CalibrationMath.cpp \
    $$PWD/../../src/CameraCalibration.cpp \
    $$PWD/../../src/CloudPointMapper.cpp \
    $$PWD/../../src/PointCalculator.cpp \
    $$PWD/../../src/VariableManager.cpp

HEADERS += \
    $$PWD/../../include/CalibrationMath.h \
    $$PWD/../../include/CameraCalibration.h \
    $$PWD/../../include/CloudPointMapper.h \
    $$PWD/../../include/PointCalculator.h \
    $$PWD/../../include/VariableManager.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
