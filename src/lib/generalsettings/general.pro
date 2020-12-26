#-------------------------------------------------
#
# Project created by QtCreator 2017-04-05T15:26:39
#
#-------------------------------------------------

QT       += core gui widgets

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../../bin/plugins/generalsetting
TEMPLATE = lib
CONFIG += plugin


SOURCES +=\
        generalsettings.cpp

HEADERS  += ../../include/isettingspage.h ../../include/iapplicationplugin.h ../../include/iwidgetpage.h \
            generalsettings.h

RESOURCES += \
    assets.qrc
