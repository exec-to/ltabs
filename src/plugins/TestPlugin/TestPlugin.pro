#-------------------------------------------------
#
# Project created by QtCreator 2017-04-22T23:28:42
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ../../../bin/plugins/testplugin
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += $$PWD/include $$PWD/../../include

SOURCES += \
    src/testplugin.cpp

HEADERS  +=\
    ../../include/isettingspage.h \
    ../../include/iapplicationplugin.h \
    ../../include/iwidgetpage.h \
    ../../include/pluginhelper.h \
    include/testplugin.h

RESOURCES += \
    assets.qrc
