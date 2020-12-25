#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T22:44:59
#
#-------------------------------------------------

QT       += core gui KWindowSystem


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = /home/roman/local/ltabs/ltabs
TEMPLATE = app


SOURCES +=\
    src/application.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pluginmanager.cpp \
    src/x11utils.cpp \
    src/settings/settingsdialog.cpp \
    src/settings/settingslistmodel.cpp \
    src/settings/settingslistwidget.cpp \
    src/gridcontrollayout.cpp \
    src/settings/config.cpp

HEADERS  += \
    src/settings/settingsdialog.h \
    src/settings/settingslistmodel.h \
    src/settings/settingslistwidget.h \
    ../include/iapplicationplugin.h \
    ../include/iwidgetpage.h \
    ../include/pluginhelper.h \
    src/application.h \
    src/mainwindow.h \
    src/pluginmanager.h \
    src/x11utils.h \
    ../include/isettingspage.h \
    src/gridcontrollayout.h \
    src/settings/config.h

RESOURCES += \
    assets/icons.qrc
