#pragma once

#include <QObject>
#include <QtWidgets>

#include "../../src/plugins/iapplicationplugin.h"

class QString;
class QWidget;

//------------------------ GeneralSettings --------------------------------//
class TestPlugin : public QObject, public IApplicationPlugin
{
    Q_OBJECT
    Q_INTERFACES(IApplicationPlugin)
    Q_PLUGIN_METADATA(IID "ru.ltabs.plugins.IApplicationPlugin" FILE "testplugin.json")

protected:
    ISettingsPage* m_settingPage;
    IWidgetPage* m_widgetPage;

public:
    TestPlugin(); // !important! initialize class members
    virtual ~TestPlugin() {  }
    virtual ISettingsPage *getSettingsPage();
    virtual IWidgetPage *getWidgetPage();

};
//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
class TestPluginSettingsPage: public ISettingsPage {
    Q_OBJECT

private:
    QWidget *m_page;
    QString m_displayName;
    QPixmap *m_icon;

public:
    TestPluginSettingsPage();
    virtual ~TestPluginSettingsPage() {  }
    virtual QWidget* page();
    virtual QString displayName() const;
    virtual QPixmap *displayIcon();
    virtual void apply();
    virtual void reject();

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//








/*#ifndef TESTPLUGIN_H
#define TESTPLUGIN_H

#include <QObject>

class TestPlugin : public IApplicationPlugin
{
public:
    TestPlugin();
};

#endif // TESTPLUGIN_H*/
