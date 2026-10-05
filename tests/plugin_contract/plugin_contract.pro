QT += core testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_plugin_contract

INCLUDEPATH += $$PWD/../../sdk

SOURCES += tst_plugin_contract.cpp
HEADERS += \
    $$PWD/../../sdk/DeltaXPluginMetadata.h \
    $$PWD/../../sdk/DeltaXPermissions.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
