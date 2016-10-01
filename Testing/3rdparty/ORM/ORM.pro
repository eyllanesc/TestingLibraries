#-------------------------------------------------
#
# Project created by QtCreator 2016-09-30T19:43:03
#
#-------------------------------------------------

QT       -= core gui
QT += sql
TARGET = ORM
TEMPLATE = lib
CONFIG += staticlib

INCLUDEPATH += $$PWD/include
INCLUDEPATH += $$PWD/include/adapters

SOURCES += $$PWD/src/orm.cpp \
    $$PWD/src/ormdatabase.cpp \
    $$PWD/src/ormgroupby.cpp \
    $$PWD/src/ormlogger.cpp \
    $$PWD/src/ormobject.cpp \
    $$PWD/src/ormorderby.cpp \
    $$PWD/src/ormwhere.cpp \
    $$PWD/src/adapters/mysqladapter.cpp \
    $$PWD/src/adapters/ormabstractadapter.cpp \
    $$PWD/src/adapters/postgresqladapter.cpp \
    $$PWD/src/adapters/sqladapter.cpp \
    $$PWD/src/adapters/sqliteadapter.cpp


HEADERS += $$PWD/include/orm.h \
    $$PWD/include/macros.h \
    $$PWD/include/ormdatabase.h \
    $$PWD/include/ormgroupby.h \
    $$PWD/include/ormlogger.h \
    $$PWD/include/ormobject.h \
    $$PWD/include/ormorderby.h \
    $$PWD/include/ormwhere.h \
    $$PWD/include/adapters/mysqladapter.h \
    $$PWD/include/adapters/ormabstractadapter.h \
    $$PWD/include/adapters/postgresqladapter.h \
    $$PWD/include/adapters/sqladapter.h \
    $$PWD/include/adapters/sqliteadapter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = $$PWD/lib
