#include "generalsettings.h"

QSettings *configuration::settings = 0;

//------------------------ GeneralSettings --------------------------------//
GeneralSettings::GeneralSettings():
    m_settingPage(nullptr),
    m_widgetPage(nullptr)
{
    setUuid(QUuid("db507711-94ad-4f54-bffd-1a7789882839"));
    configuration::Init();
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
    m_displayName("General")\
{

}

QMap<QString, QVariant> tempSettings;


//create widget for settings with single values
template<typename T, typename ParamType, typename Signal>
T* createSingleWidget( ISettingsPage* _page, Signal _signal, const char* _prop, QString _param, QVariant _default) {
    T* w = new T(); //sub of QWidget
    //w->setProperty(_prop, settings.value(_param, _default));
    QObject::connect(w, _signal, [=](ParamType val) {
        tempSettings[_param] = QVariant::fromValue(val);
    } );

    QObject::connect(_page, &ISettingsPage::restoreSettings, [=]() {
        w->setProperty(_prop, configuration::master()->value(_param, _default));
    });

    return w;
}


QStringList themesFromDirectory() {
    QDir dir;
    dir.cd(configuration::Application::themes_directory());
    return dir.entryList(QStringList() << "*.qss");
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
                configuration::UI::getKey("width"),
                QVariant::fromValue(200)
            );
        mwWidthParam->setRange(
                    configuration::UI::min_width(),
                    configuration::UI::max_width()
        );

        QComboBox *mwPositionParam = createSingleWidget<QComboBox,QString>
            (
                this,
                &QComboBox::currentTextChanged,
                "currentText",
                configuration::Application::getKey("position_on_screen"),
                QVariant::fromValue<QString>("right")
            );
        mwPositionParam->addItems(QStringList() << "left" << "right");

        QSpinBox *bsParam = createSingleWidget<QSpinBox,int>
            (
                this,
                static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                "value",
                configuration::UI::getKey("control_buttons_size"),
                QVariant::fromValue(36)
            );
        bsParam->setRange(
                    configuration::UI::min_control_buttons_width(),
                    configuration::UI::max_control_buttons_width()
        );

        QComboBox *dsDefaultParam = createSingleWidget<QComboBox,QString>
            (
                this,
                &QComboBox::currentTextChanged,
                "currentText",
                configuration::Application::getKey("virtual_desktop"),
                QVariant::fromValue<QString>("0")
            );

        int ndesktops = KWindowSystem::numberOfDesktops();
        QStringList nitems;
        for (int i = 0; i < ndesktops + 1; i++) {
            nitems << QString::number(i);
        }
        dsDefaultParam->addItems(nitems);


        QSpinBox *appOpacityParam = createSingleWidget<QSpinBox,int>
            (
                this,
                static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                "value",
                configuration::UI::getKey("opacity"),
                QVariant::fromValue(100)
            );
        appOpacityParam->setRange(0, 100);

        QComboBox *appThemeParam = createSingleWidget<QComboBox,QString>
            (
                this,
                &QComboBox::currentTextChanged,
                "currentText",
                configuration::Application::getKey("theme_name"),
                QVariant::fromValue<QString>("default.qss")
            );
        appThemeParam->addItems(themesFromDirectory());

        connect(appThemeParam, &QComboBox::currentTextChanged, [=](QString val) {
            QString themeName = configuration::Application::themes_directory() + "/" + val;
            QFile themeFile(themeName);
            themeFile.open(QFile::ReadOnly);
            if (themeFile.isOpen()) {
                QString StyleSheet = QLatin1String(themeFile.readAll());
                qApp->setStyleSheet(StyleSheet);
            }
        });

        QFormLayout *formLayout = new QFormLayout;
        formLayout->addRow(tr("&Ширина главного окна:"), mwWidthParam);
        formLayout->addRow(tr("&Позиция окна:"), mwPositionParam);
        formLayout->addRow(tr("&Размер кнопок панели управления:"), bsParam);
//        formLayout->addRow(tr("&На всех раб. столах:"), dsEnableParam);
        formLayout->addRow(tr("&Отображать на раб.столе (0 - на всех):"), dsDefaultParam);
        formLayout->addRow(tr("&Тема оформления:"), appThemeParam);
        formLayout->addRow(tr("&Прозрачность окна:"), appOpacityParam);

        m_page->setLayout(formLayout);
    }
    return m_page;
}


void GeneralSettingsPage::apply()
{
    for(auto &item: tempSettings.toStdMap()) {
        qDebug() << item.first << " : " << item.second;
        configuration::master()->setValue(item.first , item.second);
    }

    configuration::master()->sync();
    tempSettings.clear();
}


void GeneralSettingsPage::reject() {
    emit restoreSettings();
    tempSettings.clear();
}


QString GeneralSettingsPage::displayName() const {
    return m_displayName;
}


QPixmap GeneralSettingsPage::getIcon() {
    return QPixmap(":/gen/default.main.svg");
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
