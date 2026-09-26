QT = core network
CONFIG += console c++17
CONFIG -= app_bundle
TEMPLATE = app
TARGET = delta-x-cli
INCLUDEPATH += $$PWD/../include
SOURCES += $$PWD/main.cpp
HEADERS += $$PWD/../include/CliProtocol.h
