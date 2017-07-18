#-------------------------------------------------
#
# Project created by QtCreator 2013-01-10T18:31:45
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = AntsClient
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialoggame.cpp \
    thread_class_define.cpp

HEADERS  += mainwindow.h \
    dialoggame.h \
    thread_class_define.h

FORMS    += mainwindow.ui \
    dialoggame.ui
