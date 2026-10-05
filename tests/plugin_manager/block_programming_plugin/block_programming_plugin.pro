QT += core gui widgets
CONFIG += plugin c++17
TEMPLATE = lib
TARGET = BlockProgrammingPlugin
DESTDIR = $$OUT_PWD/../plugins-block

INCLUDEPATH += \
    $$PWD/../../../plugin/BlockProgramming \
    $$PWD/../../../sdk

SOURCES += \
    $$PWD/../../../plugin/BlockProgramming/BlockProgram.cpp \
    $$PWD/../../../plugin/BlockProgramming/BlockCanvas.cpp \
    $$PWD/../../../plugin/BlockProgramming/BlockProgrammingPanel.cpp \
    $$PWD/../../../plugin/BlockProgramming/BlockProgrammingPlugin.cpp

HEADERS += \
    $$PWD/../../../plugin/BlockProgramming/BlockProgram.h \
    $$PWD/../../../plugin/BlockProgramming/BlockCanvas.h \
    $$PWD/../../../plugin/BlockProgramming/BlockProgrammingPanel.h \
    $$PWD/../../../plugin/BlockProgramming/BlockProgrammingPlugin.h \
    $$PWD/../../../sdk/DeltaXCommandProvider.h \
    $$PWD/../../../sdk/DeltaXHostContext.h \
    $$PWD/../../../sdk/DeltaXPanelProvider.h \
    $$PWD/../../../sdk/DeltaXPermissions.h \
    $$PWD/../../../sdk/DeltaXPluginMetadata.h \
    $$PWD/../../../sdk/DeltaXPluginV2.h \
    $$PWD/../../../sdk/DeltaXPluginV3.h

DISTFILES += $$PWD/../../../plugin/BlockProgramming/BlockProgrammingPlugin.json

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
