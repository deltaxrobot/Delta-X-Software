QT += core gui widgets testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_plugin_manager

INCLUDEPATH += \
    $$PWD/../../../include \
    $$PWD/../../../sdk \
    $$PWD/../../..

DELTA_X_ROOT = $$clean_path($$PWD/../../..)
include($$PWD/../../../config/opencv.pri)

SOURCES += \
    tst_plugin_manager.cpp \
    $$PWD/../../../src/PluginManager.cpp \
    $$PWD/../../../src/PluginExtensionRegistry.cpp \
    $$PWD/../../../src/PluginHostContext.cpp
HEADERS += \
    $$PWD/../../../include/PluginManager.h \
    $$PWD/../../../include/PluginExtensionRegistry.h \
    $$PWD/../../../include/PluginHostContext.h \
    $$PWD/../../../include/PluginHostServices.h \
    $$PWD/../../../sdk/DeltaXPlugin.h \
    $$PWD/../../../sdk/DeltaXPluginV2.h \
    $$PWD/../../../sdk/DeltaXPluginV3.h \
    $$PWD/../../../sdk/DeltaXHostContext.h \
    $$PWD/../../../sdk/DeltaXPermissions.h \
    $$PWD/../../../sdk/DeltaXPanelProvider.h \
    $$PWD/../../../sdk/DeltaXCommandProvider.h \
    $$PWD/../../../sdk/DeltaXGScriptProvider.h \
    $$PWD/../../../sdk/DeltaXDeviceProvider.h \
    $$PWD/../../../sdk/DeltaXServiceProvider.h \
    $$PWD/../../../sdk/DeltaXPluginMetadata.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
