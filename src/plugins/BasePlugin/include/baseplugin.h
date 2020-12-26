#pragma once

#include <QObject>
#include <QtWidgets>

#include "iapplicationplugin.h"

class QString;
class QWidget;

//------------------------ GeneralSettings --------------------------------//
class BasePlugin : public QObject, public IApplicationPlugin
{
    Q_OBJECT
    Q_INTERFACES(IApplicationPlugin)
    Q_PLUGIN_METADATA(IID "ru.ltabs.plugins.IApplicationPlugin" FILE "baseplugin.json")

protected:
    ISettingsPage* m_settingPage;
    IWidgetPage* m_widgetPage;

public:
    BasePlugin(); // !important! initialize class members
    virtual ~BasePlugin() {  }
    virtual ISettingsPage *getSettingsPage();
    virtual IWidgetPage *getWidgetPage();

};
//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
class BasePluginSettingsPage: public ISettingsPage {
    Q_OBJECT

private:
    QWidget *m_page;
    QString  m_displayName;

public:
    BasePluginSettingsPage();
    virtual ~BasePluginSettingsPage() {  }
    virtual QWidget* page();
    virtual QString displayName() const;
    virtual QPixmap getIcon();
    virtual void apply();
    virtual void reject();

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//
class BasePluginWidgetPage: public IWidgetPage {
Q_OBJECT

private:
    QWidget *m_widget;
public:
    BasePluginWidgetPage();
    virtual ~BasePluginWidgetPage() {  }
    virtual QWidget* page();
    virtual QPixmap getIcon();
};



//------------------------   IWidgetPage   --------------------------------//




/*#ifndef BASEPLUGIN_H
#define BASEPLUGIN_H


class BasePlugin : public IApplicationPlugin
{
public:
    BasePlugin();
};

#endif // BASEPLUGIN_H*/
