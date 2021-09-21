TEMPLATE = subdirs

#QT       += core gui KWindowSystem

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#HEADERS  += \
#    include/iapplicationplugin.h \
#    include/iwidgetpage.h \
#    include/pluginhelper.h \
#    include/isettingspage.h \


SUBDIRS += \
    src/app/ltabs.pro \
    src/lib/generalsettings/general.pro \
    src/lib/pluginsettings \
    src/plugins/ClipboardPlugin \
    src/plugins/TestPlugin
