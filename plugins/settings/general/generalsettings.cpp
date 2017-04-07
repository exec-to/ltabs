#include "generalsettings.h"

//------------------------ GeneralSettings --------------------------------//
GeneralSettings::GeneralSettings():
    m_settingPage(nullptr),
    m_widgetPage(nullptr),
    m_settings(nullptr)
{
    setUuid(QUuid("db507711-94ad-4f54-bffd-1a7789882839"));
}

ISettingsPage* GeneralSettings::getSettingsPage()
{
    if (!m_settingPage) {
        m_settingPage = new GeneralSettingsPage(m_settings);
    }
    return m_settingPage;
}

IWidgetPage* GeneralSettings::getWidgetPage()
{
    return nullptr; //no implement for this
}

void GeneralSettings::pushSettings(QMap<QString,QString> *settings)
{
    m_settings = settings;
}

//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
GeneralSettingsPage::GeneralSettingsPage(QMap<QString, QString> *settings):
    m_page(nullptr),
    m_displayName("General"),
    m_settings(settings)
{

}

QWidget* GeneralSettingsPage::page()
{
    if (!m_page) {
        m_page = new QLabel((*m_settings)["MainWindow/DockEdge"]);
    }
    return m_page;
}

QString GeneralSettingsPage::displayName() const {
    return m_displayName;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
