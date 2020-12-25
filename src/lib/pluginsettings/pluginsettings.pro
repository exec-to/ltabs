#-------------------------------------------------
#
# Project created by QtCreator 2017-04-19T18:29:47
#
#-------------------------------------------------

QT       += core gui widgets

TARGET = ~/local/ltabs/plugins/pluginsettings
TEMPLATE = lib
CONFIG += plugin

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    pluginsettings.cpp \
    pluginhelperlistmodel.cpp

HEADERS  += ../../include/isettingspage.h ../../include/iapplicationplugin.h ../../include/iwidgetpage.h \
    ../../include/pluginhelper.h \
    pluginsettings.h \
    pluginhelperlistmodel.h

RESOURCES += \
    assets.qrc
