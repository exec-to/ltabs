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


template<typename T, typename Signal/*, typename ParamType*/>
T* createWidget( GeneralSettingsPage* _page, Signal _signal, const char* _prop, QString _param, QString _default) {
    T* w = new T(); //sub of QWidget
    //w.setProperty(_prop, settings.value(_param, _default).toString());
    QObject::connect(w, _signal, [=](QString val) {
        tempSettings[_param] = static_cast<QString>(val);
    } );

    QObject::connect(_page, &GeneralSettingsPage::restoreSettings, [=]() {
        w->setProperty(_prop, settings.value(_param, _default));
    });

    return w;
    //qobject_cast<>();
}

QWidget* GeneralSettingsPage::page()
{


    if (!m_page) {
        m_page = new QWidget();
        QLineEdit *lineWidthParam = createWidget<QLineEdit>(this, &QLineEdit::textChanged, "text", QString("MainWindow/width"), QString("250"));
        //----------------- Main window width ---------------------------
        /*QSpinBox *mwWidth= new QSpinBox();
        mwWidth->setRange(160,320);
        mwWidth->setValue(settings.value("MainWindow/width", 250).toInt());
        connect(mwWidth,
                static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                //&QSpinBox::valueChanged,
                [=](int val) {
                tempSettings["MainWindow/width"] = QString::number(val);
        });

        connect(this,
                &GeneralSettingsPage::changesRestored, [=]()
        {
            mwWidth->blockSignals(true);
            mwWidth->setValue(settings.value("MainWindow/width", 250).toInt());
            mwWidth->blockSignals(false);
        });*/
        //----------------- Main window width ---------------------------

        //----------------- Main window position ------------------------
        QComboBox *mwPosition = new QComboBox();
        mwPosition->addItems(QStringList() << "Left" << "Right");
        //mwPosition->setCurrentText(settings.value("MainWindow/DockEdge", "Right").toString());

        connect(mwPosition,
                &QComboBox::currentTextChanged,
                [=](QString val) {
                tempSettings["MainWindow/DockEdge"] = val;
        });

        connect(this,
                &GeneralSettingsPage::restoreSettings, [=]()
        {
            mwPosition->blockSignals(true);
            mwPosition->setCurrentText((settings.value("MainWindow/DockEdge", "Right").toString()));
            mwPosition->blockSignals(false);
        });
        //----------------- Main window position ------------------------


        //----------------- Control buttons size ------------------------
        /*QSpinBox *mwWidth= new QSpinBox();
        mwWidth->setRange(160,320);
        mwWidth->setValue(settings.value("MainWindow/width", 250).toInt());
        connect(mwWidth,
                static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                //&QSpinBox::valueChanged,
                [=](int val) {
                tempSettings["MainWindow/width"] = QString::number(val);
        });

        connect(this,
                &GeneralSettingsPage::changesRestored, [=]()
        {
            mwWidth->blockSignals(true);
            mwWidth->setValue(settings.value("MainWindow/width", 250).toInt());
            mwWidth->blockSignals(false);
        });*/
        //----------------- Control buttons size ------------------------

        QFormLayout *formLayout = new QFormLayout;
        //formLayout->addRow(tr("&Ширина главного окна:"), mwWidth);
        formLayout->addRow(tr("&Ширина главного окна:"), lineWidthParam);
        formLayout->addRow(tr("&Позиция окна:"), mwPosition);

        m_page->setLayout(formLayout);
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
    emit restoreSettings();
    tempSettings.clear();
}

QString GeneralSettingsPage::displayName() const {
    return m_displayName;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
