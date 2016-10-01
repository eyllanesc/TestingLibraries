#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T19:43:40
#
#-------------------------------------------------

QT       -=  gui
TARGET = SimpleCrypt
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/include

SOURCES += $$PWD/src/simplecrypt.cpp

HEADERS += $$PWD/include/simplecrypt.h
unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = $$PWD/lib
