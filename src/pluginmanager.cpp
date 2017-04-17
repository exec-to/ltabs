#include "pluginmanager.h"

QList<IApplicationPlugin *> PluginManager::pluginsList;

void PluginManager::loadPlugins() {
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


    for (auto &pluginToLoad: pluginsToLoad) {
        QPluginLoader loader(dir.absoluteFilePath(pluginToLoad->fileName));
        QObject *pluginObject = loader.instance();
        IApplicationPlugin* plugin = qobject_cast<IApplicationPlugin*>(pluginObject);

        if (plugin->getUuid() != pluginToLoad->uuid) {
            qDebug() << "bad plugin identification!";
            continue;
        }

        pluginsList.append(plugin);
    }
}
