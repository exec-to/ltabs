#include "pluginmanager.h"

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{

}

QList<ISettingsPage*> PluginManager::settingPages;
