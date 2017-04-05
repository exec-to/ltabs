#pragma once

#include <QObject>
#include <QtWidgets>
#include "controlbarlayout.h"
#include "settings/isettingspage.h"
#include <QPluginLoader>

class PluginManager : public QObject
{
    Q_OBJECT
private:
    explicit PluginManager(QObject *parent = 0);
public:
    static QList<ISettingsPage *> settingPages;
    static void LoadPlugins(QTabWidget *tabWidget, ControlBarLayout *controlLayout);

};

