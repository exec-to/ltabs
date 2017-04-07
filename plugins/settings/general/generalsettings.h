#pragma once

#include <QObject>
#include <QtWidgets>

#include "../../../plugins/iapplicationplugin.h"
#include "../../../settings/isettingspage.h"
#include "../../../plugins/iwidgetpage.h"

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
    QMap<QString,QString> *m_settings;

public:
    GeneralSettings(); // !important! initialize class members
    virtual void pushSettings(QMap<QString,QString> *settings);
    //virtual QMap<QString,QString> getSettings();
    virtual ~GeneralSettings() {  }
    virtual ISettingsPage *getSettingsPage();
    virtual IWidgetPage *getWidgetPage();

};
//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
class GeneralSettingsPage: public ISettingsPage {
    Q_OBJECT

private:
    QWidget* m_page;
    QString m_displayName;
    QMap<QString, QString> *m_settings;

public:
    GeneralSettingsPage(QMap<QString, QString> *settings);
    virtual ~GeneralSettingsPage() {  }
    virtual QWidget* page();
    virtual QString displayName() const;
    virtual QMap<QString, QString> getChangedSettings();

public slots:
    void commitChanges(const QString &data);

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
