#include "generalsettings.h"

//------------------------ GeneralSettings --------------------------------//
GeneralSettings::GeneralSettings():
    m_settingPage(nullptr),
    m_widgetPage(nullptr)
{
    setUuid(QUuid("db507711-94ad-4f54-bffd-1a7789882839"));
}

ISettingsPage* GeneralSettings::getSettingsPage()
{
    if (!m_settingPage) {
        m_settingPage = new GeneralSettingsPage();
    }
    return m_settingPage;
}

IWidgetPage* GeneralSettings::getWidgetPage()
{
    return nullptr; //no implement for this
}
//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
GeneralSettingsPage::GeneralSettingsPage():
    m_page(nullptr),
     m_displayName("General")
{

}

QWidget* GeneralSettingsPage::page()
{
    if (!m_page) {
        m_page = new QLabel("Hello QT!");
    }
    return m_page;
}

QString GeneralSettingsPage::displayName() const {
    return m_displayName;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
