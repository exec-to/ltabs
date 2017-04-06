#include "pluginmanager.h"
#include "plugins/iapplicationplugin.h"
//#include "plugins/iwidgetpage.h"
#include "settings/isettingspage.h"
#include "ltabsapplication.h"
#include "plugins/pluginhelper.h"

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

        /*if (plugin->getUuid() != pluginToLoad->uuid) {
            qDebug() << "bad plugin identification!";
            continue;
        }*/

        if (plugin->getSettingsPage() != nullptr)
            settingPages.append(plugin->getSettingsPage());

        //if (plugin->getWidgetPage()) {
        /*

        QWidget* w = new QWidget(); //plugin widget
        QPixmap icon(":" + iconFile); //plugin->icon;
        tabWidget->addTab(w, "tab" + QString::number(++x));

        QToolButton* btn = controlLayout->createControlButton(icon); //buttom for plugin widget

        QSignalMapper* mapper = new QSignalMapper();
        connect(mapper, SIGNAL(mapped(QWidget*)), tabWidget, SLOT(setCurrentWidget(QWidget*)));
        connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(btn, w);

        */
        //}

    }



    /*lstIcons << "1.png" << "2.png" << "3.png" << "4.png" << "5.png";
    for (auto &iconFile: lstIcons) { //load plugins here
        static int x = 0;

    }*/
}
