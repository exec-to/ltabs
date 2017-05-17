#pragma once

#include <QObject>
#include <QtWidgets>

#include "../../src/plugins/iapplicationplugin.h"
#include "../../src/settings/config.h"

class QString;
class QWidget;

//------------------------ GeneralSettings --------------------------------//
class GeneralSettings : public QObject, public IApplicationPlugin
{
    Q_OBJECT
    Q_INTERFACES(IApplicationPlugin)
    Q_PLUGIN_METADATA(IID "ru.ltabs.plugins.IApplicationPlugin" FILE "general.json")

protected:
    ISettingsPage *m_settingPage;
    IWidgetPage   *m_widgetPage;

public:
    GeneralSettings(); // !important! initialize class members
    ~GeneralSettings() {  }
    ISettingsPage *getSettingsPage();
    IWidgetPage *getWidgetPage();

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
    ~GeneralSettingsPage() {  }
    QWidget* page();
    QString displayName() const;
    QPixmap displayIcon();
    void apply();
    void reject();

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
