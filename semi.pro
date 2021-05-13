#-------------------------------------------------
#
# Project created by QtCreator 2020-08-26T17:40:34
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = semi
TEMPLATE = app


SOURCES += main.cpp\
        mywidget.cpp \
    menu.cpp \
    sudo.cpp

HEADERS  += mywidget.h \
    menu.h \
    sudo.h

FORMS    +=
CONFIG += c++11

RESOURCES += \
    image/resource.qrc

QT+=multimedia

OBJECTS_DIR  = tmp
MOC_DIR      = tmp

