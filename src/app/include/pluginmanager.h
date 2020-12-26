#pragma once

#include <QPluginLoader>
#include "iapplicationplugin.h"
#include "pluginhelper.h"
#include "configuration.h"


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
