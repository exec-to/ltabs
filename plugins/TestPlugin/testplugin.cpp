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
    if (!m_widgetPage) {
        m_widgetPage = new TestPluginWidgetPage();
    }
    return m_widgetPage;
}


//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
TestPluginSettingsPage::TestPluginSettingsPage():
    m_page(nullptr),
    m_displayName("TestPlugin")
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

QPixmap TestPluginSettingsPage::displayIcon() {
    QSettings settings;
    QString iconTheme = settings.value("Application/icons", "light").toString().toLower();
    if (!m_icon) {
        m_icon = QPixmap(":" + iconTheme + ".test.png");
    }
    return m_icon;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//
TestPluginWidgetPage::TestPluginWidgetPage():
    m_widget(nullptr)
{

}


QWidget* TestPluginWidgetPage::page() {
    if (!m_widget) {
        m_widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout();
        QLineEdit *line = new QLineEdit("test text");
        QPushButton *btn = new QPushButton("Press me");
        layout->addWidget(line);
        layout->addWidget(btn);
        m_widget->setLayout(layout);
    }

    return m_widget;
}

QPixmap TestPluginWidgetPage::displayIcon() {
    QSettings settings;
    QString iconTheme = settings.value("Application/icons", "light").toString().toLower();
    if (!m_icon) {
        m_icon = QPixmap(":" + iconTheme + ".test.png");
    }
    return m_icon;
}

//------------------------   IWidgetPage   --------------------------------//
