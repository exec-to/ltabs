#pragma once

#include <QObject>
#include <QtWidgets>
#include "controlbarlayout.h"
#include "settings/isettingspage.h"
#include <QPluginLoader>
#include "plugins/iapplicationplugin.h"
#include "plugins/iwidgetpage.h"
#include "ltabsapplication.h"
#include "plugins/pluginhelper.h"


class PluginManager : public QObject
{
    Q_OBJECT
private:
    explicit PluginManager(QObject *parent = 0) {  }
public:
    static QList<IApplicationPlugin *> pluginList;
    static QList<ISettingsPage *> settingPages;
    static void LoadPlugins(QTabWidget *tabWidget, ControlBarLayout *controlLayout);

};

