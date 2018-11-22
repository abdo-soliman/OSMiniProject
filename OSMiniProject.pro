#-------------------------------------------------
#
# Project created by QtCreator 2018-11-05T18:27:00
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = OSMiniProject
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    controller.cpp \
    util.cpp \
    graph.cpp \
    qcustomplot.cpp \
    scheduler/Scheduler.cpp

HEADERS  += mainwindow.h \
    controller.h \
    util.h \
    graph.h \
    qcustomplot.h \
    scheduler/Scheduler.h \
    scheduler/ProcessGenerator.h

FORMS    += mainwindow.ui \
    graph.ui
