QT += core gui widgets
CONFIG += plugin c++17
TEMPLATE = lib
TARGET = BlockProgrammingPlugin
DESTDIR = $$OUT_PWD/plugin

INCLUDEPATH += $$PWD/../../sdk

SOURCES += \
    BlockProgram.cpp \
    BlockCanvas.cpp \
    BlockProgrammingPanel.cpp \
    BlockProgrammingPlugin.cpp

HEADERS += \
    BlockProgram.h \
    BlockCanvas.h \
    BlockProgrammingPanel.h \
    BlockProgrammingPlugin.h \
    $$PWD/../../sdk/DeltaXCommandProvider.h \
    $$PWD/../../sdk/DeltaXHostContext.h \
    $$PWD/../../sdk/DeltaXPanelProvider.h \
    $$PWD/../../sdk/DeltaXPermissions.h \
    $$PWD/../../sdk/DeltaXPluginMetadata.h \
    $$PWD/../../sdk/DeltaXPluginV2.h \
    $$PWD/../../sdk/DeltaXPluginV3.h

DISTFILES += BlockProgrammingPlugin.json README.md

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
