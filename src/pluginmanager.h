#pragma once

#include <QObject>
#include <QtWidgets>
#include "gridcontrollayout.h"
#include "plugins/isettingspage.h"
#include <QPluginLoader>
#include "plugins/iapplicationplugin.h"
#include "plugins/iwidgetpage.h"
#include "plugins/pluginhelper.h"
#include "settings/config.h"


class PluginLoader : public QObject
{
    Q_OBJECT
private:
    explicit PluginLoader(QObject *parent = 0) {  }
    static QList<IApplicationPlugin *> plugins;
public:
    static QList<IApplicationPlugin *> pluginsList();
    static void load();

};
