QT += core sql
QT -= gui

CONFIG += c++11

TARGET = Testing
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    models/user.cpp


HEADERS += \
    models/user.h

INCLUDEPATH += $$PWD/3rdparty/BotanWrapper/include
LIBS += -L"$$PWD/3rdparty/BotanWrapper/lib" -lBotanWrapper

INCLUDEPATH += $$PWD/3rdparty/ORM/include
LIBS += -L"$$PWD/3rdparty/ORM/lib" -lORM

INCLUDEPATH += $$PWD/3rdparty/SimpleCrypt/include
LIBS += -L"$$PWD/3rdparty/SimpleCrypt/lib" -lSimpleCrypt


INCLUDEPATH += $$PWD/models

LIBS += -lbotan-1.11

INCLUDEPATH += /usr/include/botan-1.11

DESTDIR = $$PWD/../output


INCLUDEPATH += $$PWD/3rdparty/BotanWrapper
DEPENDPATH += $$PWD/3rdparty/BotanWrapper
