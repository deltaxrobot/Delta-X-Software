QT += core gui widgets testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_variable_manager

INCLUDEPATH += \
    $$PWD/../../include

SOURCES += \
    $$PWD/tst_variable_manager.cpp \
    $$PWD/UnityTool_stub.cpp \
    $$PWD/../../src/VariableManager.cpp

HEADERS += \
    $$PWD/../../include/ObjectInfo.h \
    $$PWD/../../include/VariableManager.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
