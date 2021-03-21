#-------------------------------------------------
#
# Project created by QtCreator 2017-03-29T22:44:59
#
#-------------------------------------------------

QT       += core gui KWindowSystem


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ../../bin/ltabs
TEMPLATE = app

INCLUDEPATH += $$PWD/include $$PWD/../include

SOURCES +=\
    src/application.cpp \
    src/configuration.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/pluginmanager.cpp \
    src/x11utils.cpp \
    src/settingsdialog.cpp \
    src/settingslistmodel.cpp \
    src/settingslistwidget.cpp \
    src/gridcontrollayout.cpp

HEADERS  += \
    ../include/iapplicationplugin.h \
    ../include/iwidgetpage.h \
    ../include/pluginhelper.h \
    ../include/isettingspage.h \
    include/configuration.h \
    include/settingsdialog.h \
    include/settingslistmodel.h \
    include/settingslistwidget.h \
    include/application.h \
    include/mainwindow.h \
    include/pluginmanager.h \
    include/x11utils.h \
    include/gridcontrollayout.h

RESOURCES += \
    assets/icons.qrc

DISTFILES += \
    notes.txt
