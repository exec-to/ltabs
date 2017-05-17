#include "generalsettings.h"

QSettings *cfg::settings = 0;

//------------------------ GeneralSettings --------------------------------//
GeneralSettings::GeneralSettings():
    m_settingPage(nullptr),
    m_widgetPage(nullptr)
{
    setUuid(QUuid("db507711-94ad-4f54-bffd-1a7789882839"));
    cfg::Init();
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


QStringList themesFromDirectory() {
    QDir dir;
    dir.cd(cfg::Application::theme_dir());
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
                cfg::MainWindow::getKey("width"),
                QVariant::fromValue(200)
            );
        mwWidthParam->setRange(160, 320);

        QComboBox *mwPositionParam = createSingleWidget<QComboBox,QString>
            (
                this,
                &QComboBox::currentTextChanged,
                "currentText",
                cfg::MainWindow::getKey("edge"),
                QVariant::fromValue<QString>("right")
            );
        mwPositionParam->addItems(QStringList() << "left" << "right");

        QSpinBox *bsParam = createSingleWidget<QSpinBox,int>
            (
                this,
                static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
                "value",
                cfg::MainWindow::getKey("button_size"),
                QVariant::fromValue(36)
            );
        bsParam->setRange(24, 64);

        QCheckBox* dsEnableParam = createSingleWidget<QCheckBox,int>
            (
                this,
                &QCheckBox::stateChanged,
                "checked",
                cfg::Environment::getKey("is_dock"),
                QVariant::fromValue(2)
            );


        QComboBox *dsDefaultParam = createSingleWidget<QComboBox,QString>
            (
                this,
                &QComboBox::currentTextChanged,
                "currentText",
                cfg::Environment::getKey("def_dt"),
                QVariant::fromValue<QString>("0")
            );

        int ndesktops = cfg::Environment::dt_num();
        QStringList nitems;
        for (int i = 0; i < ndesktops; i++) {
            nitems << QString::number(i);
        }
        dsDefaultParam->addItems(nitems);

        connect(dsEnableParam, &QCheckBox::stateChanged, [=](int state) {
            dsDefaultParam->setEnabled(!state);
        });


        QComboBox *appIconsParam = createSingleWidget<QComboBox,QString>
            (
                this,
                &QComboBox::currentTextChanged,
                "currentText",
                cfg::Application::getKey("icons_set"),
                QVariant::fromValue<QString>("dark")
            );
        appIconsParam->addItems(QStringList() << "dark" << "light");

        QComboBox *appThemeParam = createSingleWidget<QComboBox,QString>
            (
                this,
                &QComboBox::currentTextChanged,
                "currentText",
                cfg::Application::getKey("theme"),
                QVariant::fromValue<QString>("default.qss")
            );
        appThemeParam->addItems(themesFromDirectory());

        connect(appThemeParam, &QComboBox::currentTextChanged, [=](QString val) {
            QString themeName = cfg::Application::theme_dir() + "/" + val;
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
        formLayout->addRow(tr("&Размер кнопок нижней панели:"), bsParam);
        formLayout->addRow(tr("&На всех раб. столах:"), dsEnableParam);
        formLayout->addRow(tr("&Отображать на раб.столе:"), dsDefaultParam);
        formLayout->addRow(tr("&Тема иконок:"), appIconsParam);
        formLayout->addRow(tr("&Тема оформления:"), appThemeParam);

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


QPixmap GeneralSettingsPage::displayIcon() {
    QString iconTheme = cfg::Application::icons_set();
    if (!m_icon) {
        m_icon = QPixmap(":" + iconTheme + ".general.png");
    }
    return m_icon;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
