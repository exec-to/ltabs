#-------------------------------------------------
#
# Project created by QtCreator 2017-04-24T15:33:36
#
#-------------------------------------------------

QT       += core gui widgets quickwidgets #quick

TARGET = ../../../bin/plugins/clipboardplugin
TEMPLATE = lib
CONFIG += plugin qmltypes

INCLUDEPATH += $$PWD/include $$PWD/../../include

SOURCES += \
    src/clipboard.cpp \
    src/clipboardplugin.cpp

HEADERS  += \
    ../../include/isettingspage.h \
    ../../include/iapplicationplugin.h \
    ../../include/iwidgetpage.h \
    ../../include/pluginhelper.h \
    include/clipboard.h \
    include/clipboardplugin.h

RESOURCES += \
    assets.qrc \
    qml.qrc

