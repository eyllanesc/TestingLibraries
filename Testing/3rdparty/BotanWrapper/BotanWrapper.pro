#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T19:42:23
#
#-------------------------------------------------

QT       -=  gui
QT       += core
TARGET = BotanWrapper
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/include

SOURCES += $$PWD/src/botanwrapper.cpp

HEADERS += $$PWD/include/botanwrapper.h

LIBS += -lbotan-1.11

INCLUDEPATH += /usr/include/botan-1.11

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = $$PWD/lib
