QT = core network testlib
CONFIG += console testcase c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = tst_cli_transport
INCLUDEPATH += $$PWD/../../include
SOURCES += $$PWD/tst_cli_transport.cpp $$PWD/../../src/CliServer.cpp
HEADERS += $$PWD/../../include/CliServer.h $$PWD/../../include/CliProtocol.h
