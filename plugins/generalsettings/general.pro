#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T15:26:39
#
#-------------------------------------------------

QT       += core gui widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../build/plugins/generalsetting
TEMPLATE = lib
CONFIG += plugin


SOURCES +=\
        generalsettings.cpp

HEADERS  += generalsettings.h ../../src/plugins/isettingspage.h ../../src/plugins/iapplicationplugin.h ../../src/plugins/iwidgetpage.h

RESOURCES += \
    assets/general.qrc
