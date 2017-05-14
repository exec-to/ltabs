#include "pluginmanager.h"

QList<IApplicationPlugin *> PluginLoader::plugins;

QList<IApplicationPlugin *> PluginLoader::pluginsList() {
    return PluginLoader::plugins;
}

void PluginLoader::load() {
    QSettings settings;
    QString pluginsDirectory = cfg::Application::plugin_dir();
    QDir dir;
    dir.cd(pluginsDirectory);

    QList<PluginHelper *> pluginsToLoad;

    //static plugin 1
    PluginHelper* ph = new PluginHelper();
    ph->uuid = QUuid("db507711-94ad-4f54-bffd-1a7789882839");
    ph->fileName = "libgeneralsetting.so";
    pluginsToLoad.append(ph);

    //static plugin 2
    PluginHelper* ph2 = new PluginHelper();
    ph2->uuid = QUuid("5dc916d6-fa0f-4ee6-bae9-065b393a6a69");
    ph2->fileName = "libpluginsettings.so";
    pluginsToLoad.append(ph2);

    int size = settings.beginReadArray(cfg::Plugins());
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        PluginHelper *helper = new PluginHelper();
        helper->uuid = QUuid(settings.value("uuid").toString());
        helper->fileName = settings.value("fileName").toString();
        //helper->uuid = QUuid(cfg::Plugins::uuid());
        //helper->fileName = cfg::Plugins::file_name();
        pluginsToLoad.append(helper);
    }
    settings.endArray();

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
