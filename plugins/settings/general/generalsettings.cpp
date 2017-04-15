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

QMap<QString, QString> tempSettings;
QSettings settings;

QWidget* GeneralSettingsPage::page()
{
    if (!m_page) {
        QWidget *parent = new QWidget();
        //QLineEdit *txt_app_width = new QLineEdit();
        QSpinBox *mwWidth= new QSpinBox();
        mwWidth->setRange(160,320);
        mwWidth->setValue(settings.value("MainWindow/width", 250).toInt());

        QLabel *lbl_app_width = new QLabel("Ширина главного окна");

        connect(mwWidth,
                //&QLineEdit::textEdited,
                static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                //&QSpinBox::valueChanged,
                [=](int val) {
            //if (txt_app_width) {
                tempSettings["MainWindow/width"] = QString::number(val);
             //}
        });

        connect(this,
                &GeneralSettingsPage::changesRestored, [=]()
        {
            mwWidth->blockSignals(true);
            mwWidth->setValue(settings.value("MainWindow/width", 250).toInt());
            mwWidth->blockSignals(false);
        });

        QHBoxLayout *vblayout = new QHBoxLayout();
        vblayout->addWidget(lbl_app_width);
        vblayout->addWidget(mwWidth);
        parent->setLayout(vblayout);
        m_page = parent;
    }
    return m_page;
}


void GeneralSettingsPage::apply()
{
    for(auto &item: tempSettings.toStdMap()) {
        settings.setValue(item.first , item.second);
    }

    settings.sync();
    tempSettings.clear();
}

void GeneralSettingsPage::reject() {
    emit changesRestored();
    tempSettings.clear();
}

QString GeneralSettingsPage::displayName() const {
    return m_displayName;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
