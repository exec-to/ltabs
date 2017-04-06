#include "pluginmanager.h"

QList<IApplicationPlugin *> PluginManager::pluginList;
QList<ISettingsPage*> PluginManager::settingPages;


void PluginManager::LoadPlugins(QTabWidget *tabWidget, ControlBarLayout *controlLayout) {
    
    LTabsApplication* app = qobject_cast<LTabsApplication*>(LTabsApplication::instance());
    QString pluginsDirectory = app->readSetting("Application/PluginsDir");
    QDir dir;
    dir.cd(pluginsDirectory);

    QList<PluginHelper *> pluginsToLoad = app->getPluginsList();

    for (auto &pluginToLoad: pluginsToLoad) {
        QPluginLoader loader(dir.absoluteFilePath(pluginToLoad->fileName));
        QObject *pluginObject = loader.instance();
        IApplicationPlugin* plugin = qobject_cast<IApplicationPlugin*>(pluginObject);

        if (plugin->getUuid() != pluginToLoad->uuid) {
            qDebug() << "bad plugin identification!";
            continue;
        }

        ISettingsPage* settingsPage = plugin->getSettingsPage();
        if (settingsPage)
            settingPages.append(plugin->getSettingsPage());

        IWidgetPage* widgetPage = plugin->getWidgetPage();
        if (widgetPage) {
            QWidget* w = widgetPage->page();
            tabWidget->addTab(w, "tab1");

            QPixmap icon(":1.png"); //plugin->icon;
            QToolButton* btn = controlLayout->createControlButton(icon); //buttom for plugin widget
            QSignalMapper* mapper = new QSignalMapper();
            connect(mapper, SIGNAL(mapped(QWidget*)), tabWidget, SLOT(setCurrentWidget(QWidget*)));
            connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
            mapper->setMapping(btn, w);
        }

        pluginList.append(plugin);
    }
}
