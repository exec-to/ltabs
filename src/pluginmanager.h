#pragma once

#include <QPluginLoader>
#include "plugins/iapplicationplugin.h"
#include "plugins/pluginhelper.h"
#include "settings/config.h"


class PluginLoader : public QObject
{
    Q_OBJECT
private:
    explicit PluginLoader();
    static   QList<IApplicationPlugin *> plugins;


public:
    static   QList<IApplicationPlugin *> &pluginsList();
    static   void load();

};
