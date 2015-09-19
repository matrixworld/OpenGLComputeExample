#-------------------------------------------------
#
# Project created by QtCreator 2015-09-12T18:58:50
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenGLComputeExample
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    myglwidget.cpp

HEADERS  += mainwindow.h \
    myglwidget.h

FORMS    += mainwindow.ui

DISTFILES += \
    example.vs \
    example.fs \
    example.cs
