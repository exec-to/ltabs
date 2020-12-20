#include "baseplugin.h"

//------------------------ GeneralSettings --------------------------------//
BasePlugin::BasePlugin():
    m_settingPage(nullptr),
    m_widgetPage(nullptr)
{
    setUuid(QUuid("c89088f1-ab51-47a8-beb8-e178e1b176d3"));
}

ISettingsPage* BasePlugin::getSettingsPage()
{
    if (!m_settingPage) {
        m_settingPage = new BasePluginSettingsPage();
    }
    return m_settingPage;
}

IWidgetPage* BasePlugin::getWidgetPage()
{
    if (!m_widgetPage) {
        m_widgetPage = new BasePluginWidgetPage();
    }
    return m_widgetPage;
}


//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
BasePluginSettingsPage::BasePluginSettingsPage():
    m_page(nullptr),
    m_displayName("BasePlugin")
{

}

QWidget* BasePluginSettingsPage::page()
{
    if (!m_page) {
        m_page = new QWidget();
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow(tr("&Базовые настройки:"), new QLineEdit("Hello base"));
        m_page->setLayout(formLayout);
    }
    return m_page;
}


void BasePluginSettingsPage::apply()
{

}

void BasePluginSettingsPage::reject() {

}

QString BasePluginSettingsPage::displayName() const {
    return m_displayName;
}

QPixmap BasePluginSettingsPage::displayIcon() {
    QSettings settings;
    QString iconTheme = settings.value("Application/icons", "light").toString().toLower();
//    qDebug() << "BasePlugin.iconTheme: " << iconTheme;
    qDebug() << "Test settings: " << settings.value("Application/icons");
    if (!m_icon) {
        qDebug() << "BasePlugin.icon: " << ":" + iconTheme + ".base.png";
        m_icon = QPixmap(":" + iconTheme + ".base.png");
    }
    return m_icon;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//
BasePluginWidgetPage::BasePluginWidgetPage():
    m_widget(nullptr)
{

}


QWidget* BasePluginWidgetPage::page() {
    if (!m_widget) {
        m_widget = new QWidget();
        QHBoxLayout *layout = new QHBoxLayout();
        QLineEdit *line = new QLineEdit("base plugin");
        QPushButton *btn = new QPushButton("Fix me");
        btn->setToolTip("FIX");
        layout->addWidget(line);
        layout->addWidget(btn);
        m_widget->setLayout(layout);
    }

    return m_widget;
}

QPixmap BasePluginWidgetPage::displayIcon() {
    QSettings settings;
    QString iconTheme = settings.value("Application/icons", "light").toString().toLower();
    if (!m_icon) {
        m_icon = QPixmap(":" + iconTheme + ".test.png");
    }
    return m_icon;
}

//------------------------   IWidgetPage   --------------------------------//
