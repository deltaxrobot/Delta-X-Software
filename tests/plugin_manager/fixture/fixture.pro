QT += core widgets
CONFIG += plugin c++17
TEMPLATE = lib
TARGET = DeltaXTestPlugin
DESTDIR = $$OUT_PWD/../plugins

INCLUDEPATH += $$PWD/../../../sdk

SOURCES += FakePlugin.cpp
HEADERS += \
    FakePlugin.h \
    $$PWD/../../../sdk/DeltaXPluginV2.h \
    $$PWD/../../../sdk/DeltaXPanelProvider.h \
    $$PWD/../../../sdk/DeltaXCommandProvider.h \
    $$PWD/../../../sdk/DeltaXPluginMetadata.h
DISTFILES += FakePlugin.json

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
