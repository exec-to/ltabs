#include "pluginmanager.h"

QList<IApplicationPlugin *> PluginLoader::plugins;


void PluginLoader::load() {

    QDir dir;
    dir.cd(cfg::Application::plugin_dir());

    QList<PluginHelper *> loadList;

    //general settings module
    PluginHelper* generalSettingsTab = new PluginHelper
        ("db507711-94ad-4f54-bffd-1a7789882839", "libgeneralsetting.so");
    loadList.append(generalSettingsTab);

    //plugin settings module
    PluginHelper* pluginSettingsTab = new PluginHelper
        ("5dc916d6-fa0f-4ee6-bae9-065b393a6a69", "libpluginsettings.so");
    loadList.append(pluginSettingsTab);

    int size = cfg::master()->beginReadArray(cfg::Plugins());
    for (int i = 0; i < size; ++i) {
        cfg::master()->setArrayIndex(i);
        loadList.append(new PluginHelper(cfg::Plugins::uuid(), cfg::Plugins::file_name()));
    }
    cfg::master()->endArray();

    for (auto &p: loadList) {
        QPluginLoader loader(dir.absoluteFilePath(p->fileName));
        QObject *pObj = loader.instance();

        IApplicationPlugin* plugin = qobject_cast<IApplicationPlugin*>(pObj);

        if (plugin->getUuid() != p->uuid) {
            qDebug() << "bad plugin identification!";
            continue;
        }

        plugins.append(plugin);
    }
}


QList<IApplicationPlugin *> &PluginLoader::pluginsList() {
    return PluginLoader::plugins;
}


PluginLoader::PluginLoader() {  }
