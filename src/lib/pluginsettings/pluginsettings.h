#pragma once

#include <QObject>
#include <QtWidgets>

#include "../../include/iapplicationplugin.h"
#include "../../include/pluginhelper.h"
#include "../../app/src/settings/config.h"
#include "pluginhelperlistmodel.h"
#include <QFileDialog>

class QString;
class QWidget;

//------------------------ GeneralSettings --------------------------------//
class PluginSettings : public QObject, public IApplicationPlugin
{
    Q_OBJECT
    Q_INTERFACES(IApplicationPlugin)
    Q_PLUGIN_METADATA(IID "ru.ltabs.plugins.IApplicationPlugin" FILE "plugin.json")

protected:
    ISettingsPage *m_settingPage;
    IWidgetPage   *m_widgetPage;

public:
    PluginSettings(); // !important! initialize class members
    ~PluginSettings() {  }
    ISettingsPage *getSettingsPage();
    IWidgetPage *getWidgetPage();

};
//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
class PluginSettingsPage: public ISettingsPage {
    Q_OBJECT

private:
    QWidget *m_page;
    QString  m_displayName;
    QString  getPluginFileName();
    void     currentChanged(const QModelIndex &current);

public:
    PluginSettingsPage();
    ~PluginSettingsPage() {  }
    QWidget* page();
    QString displayName() const;
    QPixmap getIcon();
    void apply();
    void reject();

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
