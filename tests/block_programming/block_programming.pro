QT += core testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_block_programming

INCLUDEPATH += \
    $$PWD/../.. \
    $$PWD/../../include \
    $$PWD/../../sdk \
    $$PWD/../../plugin/BlockProgramming

SOURCES += \
    $$PWD/tst_block_programming.cpp \
    $$PWD/../../plugin/BlockProgramming/BlockProgram.cpp \
    $$PWD/../../src/GScriptAnalyzer.cpp \
    $$PWD/../../src/PluginExtensionRegistry.cpp

HEADERS += \
    $$PWD/../../plugin/BlockProgramming/BlockProgram.h \
    $$PWD/../../include/GScriptAnalyzer.h \
    $$PWD/../../include/PluginExtensionRegistry.h \
    $$PWD/../../sdk/DeltaXDeviceProvider.h \
    $$PWD/../../sdk/DeltaXGScriptProvider.h \
    $$PWD/../../sdk/DeltaXServiceProvider.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
