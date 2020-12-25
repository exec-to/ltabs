#-------------------------------------------------
#
# Project created by QtCreator 2017-04-22T23:28:42
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ~/local/ltabs/plugins/testplugin
TEMPLATE = lib
CONFIG += plugin

SOURCES += \
    testplugin.cpp

HEADERS  += ../../include/isettingspage.h ../../include/iapplicationplugin.h ../../include/iwidgetpage.h \
    testplugin.h

RESOURCES += \
    assets.qrc
