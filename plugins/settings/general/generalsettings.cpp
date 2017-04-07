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

/*QMap<QString,QString> *GeneralSettings::getSettings()
{
    return m_settings;
}*/

//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
GeneralSettingsPage::GeneralSettingsPage(QMap<QString, QString> *settings):
    m_page(nullptr),
    m_displayName("General"),
    m_settings(settings)
{

}

QMap<QString, QString> tempSettingsTable;

QWidget* GeneralSettingsPage::page()
{
    if (!m_page) {
        QWidget *parent = new QWidget();
        QLineEdit *txt_app_width = new QLineEdit();
        //txt_app_width->set
        txt_app_width->setText((*m_settings)["MainWindow/Width"]);
        txt_app_width->setProperty("key", "MainWindow/Width");
        QLabel *lbl_app_width = new QLabel("Ширина главного окна");
        lbl_app_width->setBuddy(txt_app_width);

        connect(txt_app_width, SIGNAL(textChanged(const QString&)),
                this, SLOT(commitChanges(const QString&)));


        QVBoxLayout *vblayout = new QVBoxLayout();
        vblayout->addWidget(lbl_app_width);
        vblayout->addWidget(txt_app_width);
        parent->setLayout(vblayout);
        m_page = parent;
    }
    return m_page;
}

void GeneralSettingsPage::commitChanges(const QString &data) {
    QObject *s = sender();
    QString key = s->property("key").toString();
    tempSettingsTable[key] = data;
}

QMap<QString, QString> GeneralSettingsPage::getChangedSettings()
{
    QMap<QString, QString> settings = tempSettingsTable;
    tempSettingsTable.clear();
    return settings;
}

QString GeneralSettingsPage::displayName() const {
    return m_displayName;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
