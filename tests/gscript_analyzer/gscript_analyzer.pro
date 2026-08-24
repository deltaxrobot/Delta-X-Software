QT += core testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_gscript_analyzer

INCLUDEPATH += $$PWD/../.. $$PWD/../../include $$PWD/../../sdk

SOURCES += \
    $$PWD/tst_gscript_analyzer.cpp \
    $$PWD/../../src/GScriptAnalyzer.cpp \
    $$PWD/../../src/GScriptEditorSupport.cpp \
    $$PWD/../../src/PluginExtensionRegistry.cpp

HEADERS += \
    $$PWD/../../include/GScriptAnalyzer.h \
    $$PWD/../../include/GScriptEditorSupport.h \
    $$PWD/../../include/PluginExtensionRegistry.h \
    $$PWD/../../sdk/DeltaXDeviceProvider.h \
    $$PWD/../../sdk/DeltaXGScriptProvider.h \
    $$PWD/../../sdk/DeltaXServiceProvider.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
