#include "pluginmanager.h"

QList<IApplicationPlugin *> PluginManager::plugins;


void PluginManager::load() {

    QDir dir;
    dir.cd(configuration::Application::plugins_directory());

    QList<PluginHelper *> loadList;

    //general settings module
    PluginHelper* generalSettingsTab = new PluginHelper
        ("db507711-94ad-4f54-bffd-1a7789882839", "libgeneralsetting.so");
    loadList.append(generalSettingsTab);

    //plugin settings module
    PluginHelper* pluginSettingsTab = new PluginHelper
        ("5dc916d6-fa0f-4ee6-bae9-065b393a6a69", "libpluginsettings.so");
    loadList.append(pluginSettingsTab);

    int size = configuration::master()->beginReadArray(configuration::Plugins());
    for (int i = 0; i < size; ++i) {
        configuration::master()->setArrayIndex(i);
        loadList.append(new PluginHelper(configuration::Plugins::uuid(), configuration::Plugins::file_name()));
    }
    configuration::master()->endArray();

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


QList<IApplicationPlugin *> &PluginManager::pluginsList() {
    return PluginManager::plugins;
}


PluginManager::PluginManager() {  }
