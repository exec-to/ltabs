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
    desktoputils.cpp \
    controlbarlayout.cpp \
    settings/settingsdialog.cpp \
    settings/settingslistitem.cpp \
    settings/settingslistmodel.cpp \
    settings/settingslistwidget.cpp \
    pluginmanager.cpp

HEADERS  += mainboardwidget.h \
    desktoputils.h \
    controlbarlayout.h \
    settings/settingsdialog.h \
    settings/settingslistitem.h \
    settings/settingslistmodel.h \
    settings/isettingspage.h \
    settings/settingslistwidget.h \
    pluginmanager.h \
    plugins/iapplicationplugin.h \
    plugins/iwidgetpage.h \
    plugins/pluginhelper.h

RESOURCES += \
    assets/icons.qrc
