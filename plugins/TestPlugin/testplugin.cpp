#include "testplugin.h"

//------------------------ GeneralSettings --------------------------------//
TestPlugin::TestPlugin():
    m_settingPage(nullptr),
    m_widgetPage(nullptr)
{
    setUuid(QUuid("46668af6-7ba6-4661-9ce0-a505937d0ffa"));
}

ISettingsPage* TestPlugin::getSettingsPage()
{
    if (!m_settingPage) {
        m_settingPage = new TestPluginSettingsPage();
    }
    return m_settingPage;
}

IWidgetPage* TestPlugin::getWidgetPage()
{
    return nullptr; //no implement for this
}


//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
TestPluginSettingsPage::TestPluginSettingsPage():
    m_page(nullptr),
    m_displayName("TestPlugin"),
    m_icon(nullptr)
{

}

QWidget* TestPluginSettingsPage::page()
{
    if (!m_page) {
        m_page = new QWidget();
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow(tr("&Тестовые настройки:"), new QLineEdit("Hello test"));
        m_page->setLayout(formLayout);
    }
    return m_page;
}


void TestPluginSettingsPage::apply()
{

}

void TestPluginSettingsPage::reject() {

}

QString TestPluginSettingsPage::displayName() const {
    return m_displayName;
}

QPixmap *TestPluginSettingsPage::displayIcon() {
    if (!m_icon) {
        m_icon = new QPixmap();
    }
    return m_icon;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
