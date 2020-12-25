#pragma once

#include <QObject>
#include <QtWidgets>

#include "../../include/iapplicationplugin.h"
#include "../../app/src/settings/config.h"

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

public:
    GeneralSettingsPage();
    ~GeneralSettingsPage() {  }
    QWidget* page();
    QString displayName() const;
    QPixmap getIcon();
    void apply();
    void reject();

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
