#include "clipboardplugin.h"
#include "clipboard.h"

//------------------------ GeneralSettings --------------------------------//
ClipboardPlugin::ClipboardPlugin():
    m_settingPage(nullptr),
    m_widgetPage(nullptr)
{
    setUuid(QUuid("c89088f1-ab51-47a8-beb8-e178e1b176d3"));
}

ISettingsPage* ClipboardPlugin::getSettingsPage()
{
    if (!m_settingPage) {
        m_settingPage = new ClipboardPluginSettingsPage();
    }
    return m_settingPage;
}

IWidgetPage* ClipboardPlugin::getWidgetPage()
{
    if (!m_widgetPage) {
        m_widgetPage = new ClipboardPluginWidgetPage();
    }
    return m_widgetPage;
}


//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
ClipboardPluginSettingsPage::ClipboardPluginSettingsPage():
    m_page(nullptr),
    m_displayName("ClipboardPlugin")
{

}

QWidget* ClipboardPluginSettingsPage::page()
{
    if (!m_page) {
        m_page = new QWidget();
        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow(tr("&Базовые настройки:"), new QLineEdit("Hello clipboard"));
        m_page->setLayout(formLayout);
    }
    return m_page;
}


void ClipboardPluginSettingsPage::apply()
{

}

void ClipboardPluginSettingsPage::reject() {

}

QString ClipboardPluginSettingsPage::displayName() const {
    return m_displayName;
}

QPixmap ClipboardPluginSettingsPage::getIcon() {
    return QPixmap(":/clipboardplugin/default.main.svg");
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//
ClipboardPluginWidgetPage::ClipboardPluginWidgetPage():
    m_widget(nullptr)
{

}

/*
Example: Using QML widgets
*/
QWidget* ClipboardPluginWidgetPage::page() {
    if (!m_widget) {
//        m_widget = new QWidget();
//        QHBoxLayout *layout = new QHBoxLayout();
//        QLineEdit *line = new QLineEdit("clipboard plugin");
//        QPushButton *btn = new QPushButton("Fix me");

//        layout->addWidget(line);
//        layout->addWidget(btn);

        ClipboardModel model;
        qmlRegisterType<ClipboardModel>("ClipboardModel", 1, 0, "ClipboardModel");

        m_quickWidget = new QQuickWidget();
        m_quickWidget->setSource(QUrl("qrc:/main.qml"));
        m_quickWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);

//        layout->addWidget(m_quickWidget);
//        m_widget->setLayout(layout);
    }

    return m_quickWidget;
}

QPixmap ClipboardPluginWidgetPage::getIcon() {
    return QPixmap(":/clipboardplugin/default.main.svg");
}

//------------------------   IWidgetPage   --------------------------------//
