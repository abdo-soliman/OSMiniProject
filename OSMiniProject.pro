#-------------------------------------------------
#
# Project created by QtCreator 2018-11-05T18:27:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSMiniProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller.cpp \
    util.cpp

HEADERS  += mainwindow.h \
    controller.h \
    util.h

FORMS    += mainwindow.ui
