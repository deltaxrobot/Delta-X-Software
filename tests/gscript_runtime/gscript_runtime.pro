QT += core gui widgets testlib network serialport opengl printsupport multimedia svg concurrent
greaterThan(QT_MAJOR_VERSION, 5): QT += svgwidgets
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_gscript_runtime

INCLUDEPATH += \
    $$PWD/../.. \
    $$PWD/../../include \
    $$PWD/../../include/device \
    $$PWD/../../sdk

DELTA_X_ROOT = $$clean_path($$PWD/../..)
include($$DELTA_X_ROOT/config/opencv.pri)

SOURCES += \
    $$PWD/tst_gscript_runtime.cpp \
    $$PWD/SoftwareManager_stub.cpp \
    $$PWD/../../src/UnityTool.cpp \
    $$PWD/../../src/GcodeScript.cpp \
    $$PWD/../../src/GScriptAnalyzer.cpp \
    $$PWD/../../src/CloudPointMapper.cpp \
    $$PWD/../../src/VariableManager.cpp

HEADERS += \
    $$PWD/../../include/GcodeScript.h \
    $$PWD/../../include/GScriptAnalyzer.h \
    $$PWD/../../include/CloudPointMapper.h \
    $$PWD/../../include/VariableManager.h

FORMS += $$PWD/../../ui/GcodeReference.ui

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus /permissive- /bigobj /FS
}
