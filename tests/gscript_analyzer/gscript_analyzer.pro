QT += core testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_gscript_analyzer

INCLUDEPATH += $$PWD/../../include

SOURCES += \
    $$PWD/tst_gscript_analyzer.cpp \
    $$PWD/../../src/GScriptAnalyzer.cpp \
    $$PWD/../../src/GScriptEditorSupport.cpp

HEADERS += \
    $$PWD/../../include/GScriptAnalyzer.h \
    $$PWD/../../include/GScriptEditorSupport.h

win32:msvc* {
    QMAKE_CXXFLAGS += /std:c++17 /Zc:__cplusplus
}
