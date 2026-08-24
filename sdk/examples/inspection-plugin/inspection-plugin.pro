QT += core gui widgets
CONFIG += plugin c++17
TEMPLATE = lib
TARGET = DeltaXInspectionPlugin
DESTDIR = $$OUT_PWD/plugin

INCLUDEPATH += $$PWD/../..

SOURCES += InspectionPlugin.cpp
HEADERS += \
    InspectionPlugin.h \
    $$PWD/../../DeltaXPluginMetadata.h \
    $$PWD/../../DeltaXPermissions.h \
    $$PWD/../../DeltaXPluginV2.h \
    $$PWD/../../DeltaXPluginV3.h \
    $$PWD/../../DeltaXHostContext.h \
    $$PWD/../../DeltaXPanelProvider.h \
    $$PWD/../../DeltaXCommandProvider.h \
    $$PWD/../../DeltaXGScriptProvider.h \
    $$PWD/../../DeltaXServiceProvider.h
DISTFILES += InspectionPlugin.json README.md

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
