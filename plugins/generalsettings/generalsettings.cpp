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
    m_displayName("General"),
    m_icon(nullptr)
{

}

QMap<QString, QVariant> tempSettings;
QSettings settings;

//create widget for settings with single values
template<typename T, typename ParamType, typename Signal>
T* createSingleWidget( ISettingsPage* _page, Signal _signal, const char* _prop, QString _param, QVariant _default) {
    T* w = new T(); //sub of QWidget
    //w->setProperty(_prop, settings.value(_param, _default));
    QObject::connect(w, _signal, [=](ParamType val) {
        tempSettings[_param] = QVariant::fromValue(val);
    } );

    QObject::connect(_page, &ISettingsPage::restoreSettings, [=]() {
        w->setProperty(_prop, settings.value(_param, _default));
    });

    return w;
}

QWidget* GeneralSettingsPage::page()
{
    if (!m_page) {
        m_page = new QWidget();
        /*QLineEdit *lineWidthParam = createWidget<QLineEdit,QString>(
         * this,
         * &QLineEdit::textChanged,
         * "text",
         * QString("MainWindow/width"),
         * QString("210"));*/

        QSpinBox *mwWidthParam = createSingleWidget<QSpinBox,int>
            (
                this,
                static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                "value",
                QString("MainWindow/width"),
                QVariant::fromValue(250)
            );
        mwWidthParam->setRange(160, 320);

        QComboBox *mwPositionParam = createSingleWidget<QComboBox,QString>
            (
                this,
                &QComboBox::currentTextChanged,
                "currentText",
                QString("MainWindow/DockEdge"),
                QVariant::fromValue<QString>("Right")
            );
        mwPositionParam->addItems(QStringList() << "Left" << "Right");

        QSpinBox *bsParam = createSingleWidget<QSpinBox,int>
            (
                this,
                static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                "value",
                QString("ControlButtons/Size"),
                QVariant::fromValue(40)
            );
        bsParam->setRange(24, 64);

        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow(tr("&Ширина главного окна:"), mwWidthParam);
        formLayout->addRow(tr("&Позиция окна:"), mwPositionParam);
        formLayout->addRow(tr("&Размер кнопок нижней панели:"), bsParam);

        m_page->setLayout(formLayout);
    }
    return m_page;
}


void GeneralSettingsPage::apply()
{
    for(auto &item: tempSettings.toStdMap()) {
        qDebug() << item.first << " : " << item.second;
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

QPixmap *GeneralSettingsPage::displayIcon() {
    if (!m_icon) {
        m_icon = new QPixmap(":general.png");
    }
    return m_icon;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
