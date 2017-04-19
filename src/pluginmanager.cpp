#include "pluginmanager.h"

QList<IApplicationPlugin *> PluginLoader::plugins;

QList<IApplicationPlugin *> PluginLoader::pluginsList() {
    return PluginLoader::plugins;
}

void PluginLoader::load() {
    QSettings settings;
    QString pluginsDirectory = settings.value("Application/PluginsDir").toString();
    QDir dir;
    dir.cd(pluginsDirectory);

    QList<PluginHelper *> pluginsToLoad;

    //from qsettings;
    PluginHelper* ph = new PluginHelper();
    ph->uuid = QUuid("db507711-94ad-4f54-bffd-1a7789882839");
    ph->isActive = true;
    ph->isPrivate = true;
    ph->fileName = "libgeneralsetting.so";
    pluginsToLoad.append(ph);

    //from qsettings;
    PluginHelper* ph2 = new PluginHelper();
    ph2->uuid = QUuid("5dc916d6-fa0f-4ee6-bae9-065b393a6a69");
    ph2->isActive = true;
    ph2->isPrivate = true;
    ph2->fileName = "libpluginsettings.so";
    pluginsToLoad.append(ph2);



    for (auto &pluginToLoad: pluginsToLoad) {
        QPluginLoader loader(dir.absoluteFilePath(pluginToLoad->fileName));
        QObject *pluginObject = loader.instance();
        IApplicationPlugin* plugin = qobject_cast<IApplicationPlugin*>(pluginObject);

        if (plugin->getUuid() != pluginToLoad->uuid) {
            qDebug() << "bad plugin identification!";
            continue;
        }

        plugins.append(plugin);
    }
}
