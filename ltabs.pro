#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T22:44:59
#
#-------------------------------------------------

QT       += core gui x11extras sql
LIBS     += -lX11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ltabs
TEMPLATE = app


SOURCES += main.cpp\
    mainboardwidget.cpp \
    ltabsapplication.cpp \
    desktoputils.cpp \
    ltabssettings.cpp \
    ltabssettingsdialog.cpp \
    controlbarlayout.cpp

HEADERS  += mainboardwidget.h \
    ltabsapplication.h \
    desktoputils.h \
    ltabssettings.h \
    ltabssettingsdialog.h \
    controlbarlayout.h
