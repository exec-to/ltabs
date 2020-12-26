#-------------------------------------------------
#
# Project created by QtCreator 2017-04-24T15:33:36
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ../../../bin/plugins/baseplugin
TEMPLATE = lib
CONFIG += plugin

INCLUDEPATH += $$PWD/include $$PWD/../../include

SOURCES += \
    src/baseplugin.cpp

HEADERS  += \
    ../../include/isettingspage.h \
    ../../include/iapplicationplugin.h \
    ../../include/iwidgetpage.h \
    ../../include/pluginhelper.h \
    include/baseplugin.h

RESOURCES += \
    assets.qrc

