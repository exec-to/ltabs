#pragma once

#include <QObject>
#include <QtWidgets>

#include "../../src/plugins/iapplicationplugin.h"
#include "../../src/plugins/pluginhelper.h"
#include "../../src/settings/config.h"
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
    ISettingsPage* m_settingPage;
    IWidgetPage* m_widgetPage;

public:
    PluginSettings(); // !important! initialize class members
    virtual ~PluginSettings() {  }
    virtual ISettingsPage *getSettingsPage();
    virtual IWidgetPage *getWidgetPage();

};
//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
class PluginSettingsPage: public ISettingsPage {
    Q_OBJECT

private:
    QWidget *m_page;
    QString  m_displayName;
    QPixmap  m_icon;
    QString getPluginFileName();
    void currentChanged(const QModelIndex &current);

public:
    PluginSettingsPage();
    virtual ~PluginSettingsPage() {  }
    virtual QWidget* page();
    virtual QString displayName() const;
    virtual QPixmap displayIcon();
    virtual void apply();
    virtual void reject();

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
