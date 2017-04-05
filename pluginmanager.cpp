#include "pluginmanager.h"
#include "plugins/iapplicationplugin.h"
//#include "plugins/iwidgetpage.h"
#include "settings/isettingspage.h"

PluginManager::PluginManager(QObject *parent) : QObject(parent)
{

}

QList<ISettingsPage*> PluginManager::settingPages;

QStringList lstIcons;

void PluginManager::LoadPlugins(QTabWidget *tabWidget, ControlBarLayout *controlLayout) {

    QDir dir;
    dir.cd("plugins");
    QPluginLoader loader(dir.absoluteFilePath("libgeneralsetting.so"));
    QObject *pluginObject = loader.instance();
    IApplicationPlugin* plugin = qobject_cast<IApplicationPlugin*>(pluginObject);
    settingPages.append(plugin->getSettingsPage());

    /*lstIcons << "1.png" << "2.png" << "3.png" << "4.png" << "5.png";
    for (auto &iconFile: lstIcons) { //load plugins here
        static int x = 0;
        QWidget* w = new QWidget(); //plugin widget
        QPixmap icon(":" + iconFile); //plugin->icon;
        tabWidget->addTab(w, "tab" + QString::number(++x));

        QToolButton* btn = controlLayout->createControlButton(icon); //buttom for plugin widget

        QSignalMapper* mapper = new QSignalMapper();
        connect(mapper, SIGNAL(mapped(QWidget*)), tabWidget, SLOT(setCurrentWidget(QWidget*)));
        connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(btn, w);
    }*/
}
