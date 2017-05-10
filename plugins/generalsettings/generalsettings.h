#pragma once

#include <QObject>
#include <QtWidgets>

#include "../../src/plugins/iapplicationplugin.h"

class QString;
class QWidget;

//------------------------ GeneralSettings --------------------------------//
class GeneralSettings : public QObject, public IApplicationPlugin
{
    Q_OBJECT
    Q_INTERFACES(IApplicationPlugin)
    Q_PLUGIN_METADATA(IID "ru.ltabs.plugins.IApplicationPlugin" FILE "general.json")

protected:
    ISettingsPage* m_settingPage;
    IWidgetPage* m_widgetPage;

public:
    GeneralSettings(); // !important! initialize class members
    virtual ~GeneralSettings() {  }
    virtual ISettingsPage *getSettingsPage();
    virtual IWidgetPage *getWidgetPage();

};
//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
class GeneralSettingsPage: public ISettingsPage {
    Q_OBJECT

private:
    QWidget *m_page;
    QString  m_displayName;
    QPixmap  m_icon;

public:
    GeneralSettingsPage();
    virtual ~GeneralSettingsPage() {  }
    virtual QWidget* page();
    virtual QString displayName() const;
    virtual QPixmap displayIcon();
    virtual void apply();
    virtual void reject();

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
