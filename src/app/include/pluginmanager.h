#pragma once

#include <QPluginLoader>
#include "iapplicationplugin.h"
#include "pluginhelper.h"
#include "configuration.h"


class PluginManager : public QObject
{
    Q_OBJECT
private:
    explicit PluginManager();
    static   QList<IApplicationPlugin *> plugins;


public:
    static   QList<IApplicationPlugin *> &pluginsList();
    static   void load();

};
