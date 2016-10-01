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

SOURCES += src/orm.cpp \
    src/ormdatabase.cpp \
    src/ormgroupby.cpp \
    src/ormlogger.cpp \
    src/ormobject.cpp \
    src/ormorderby.cpp \
    src/ormwhere.cpp \
    src/adapters/mysqladapter.cpp \
    src/adapters/ormabstractadapter.cpp \
    src/adapters/postgresqladapter.cpp \
    src/adapters/sqladapter.cpp \
    src/adapters/sqliteadapter.cpp


HEADERS += include/orm.h \
    include/macros.h \
    include/ormdatabase.h \
    include/ormgroupby.h \
    include/ormlogger.h \
    include/ormobject.h \
    include/ormorderby.h \
    include/ormwhere.h \
    include/adapters/mysqladapter.h \
    include/adapters/ormabstractadapter.h \
    include/adapters/postgresqladapter.h \
    include/adapters/sqladapter.h \
    include/adapters/sqliteadapter.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}

DESTDIR = $$PWD/lib
