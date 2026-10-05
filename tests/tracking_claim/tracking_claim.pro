QT += core gui widgets testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_tracking_claim

INCLUDEPATH += \
    $$PWD/../../include

SOURCES += \
    $$PWD/tst_tracking_claim.cpp \
    $$PWD/UnityTool_stub.cpp \
    $$PWD/../../src/TrackingManager.cpp \
    $$PWD/../../src/VariableManager.cpp

HEADERS += \
    $$PWD/../../include/ObjectInfo.h \
    $$PWD/../../include/TrackingManager.h \
    $$PWD/../../include/VariableManager.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
