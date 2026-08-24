QT += core
CONFIG += plugin c++17
TEMPLATE = lib
TARGET = DeltaXV3TestPlugin
DESTDIR = $$OUT_PWD/../plugins-v3

INCLUDEPATH += $$PWD/../../../sdk

SOURCES += FakeV3Plugin.cpp
HEADERS += \
    FakeV3Plugin.h \
    $$PWD/../../../sdk/DeltaXPluginV2.h \
    $$PWD/../../../sdk/DeltaXPluginV3.h \
    $$PWD/../../../sdk/DeltaXHostContext.h \
    $$PWD/../../../sdk/DeltaXDeviceProvider.h \
    $$PWD/../../../sdk/DeltaXGScriptProvider.h \
    $$PWD/../../../sdk/DeltaXCommandProvider.h \
    $$PWD/../../../sdk/DeltaXServiceProvider.h \
    $$PWD/../../../sdk/DeltaXPluginMetadata.h \
    $$PWD/../../../sdk/DeltaXPermissions.h
DISTFILES += FakeV3Plugin.json

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
