#include "pluginsettings.h"

//------------------------ PluginSettings --------------------------------//
PluginSettings::PluginSettings():
    m_settingPage(nullptr),
    m_widgetPage(nullptr)
{
    setUuid(QUuid("5dc916d6-fa0f-4ee6-bae9-065b393a6a69"));
}

ISettingsPage* PluginSettings::getSettingsPage()
{
    if (!m_settingPage) {
        m_settingPage = new PluginSettingsPage();
    }
    return m_settingPage;
}

IWidgetPage* PluginSettings::getWidgetPage()
{
    return nullptr; //no implement for this
}


//------------------------ PluginSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
PluginSettingsPage::PluginSettingsPage():
    m_page(nullptr),
    m_displayName("Plugins"),
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

QWidget* PluginSettingsPage::page()
{

    if (!m_page) {
        m_page = new QWidget();

        QFormLayout *formLayout = new QFormLayout;
        QPushButton *addButton = new QPushButton("Выбрать...");
        formLayout->addRow(tr("&Загрузка плагинов:"), addButton);
        QListView *plugins = new QListView();
        PluginHelperListModel *model = new PluginHelperListModel();
        model->load();
        plugins->setModel(model);
        formLayout->addWidget(plugins);

        connect(addButton, &QPushButton::clicked, [=]() {
            QString pluginsDirectory = settings.value("Application/PluginsDir").toString();
            QDir dir;
            dir.cd(pluginsDirectory);
            QString filename = QFileDialog::getOpenFileName(m_page,
                                                    QString("Добавить плагин"),
                                                    dir.absolutePath());
            model->add(filename);
        });

        QPushButton* removeButton = new QPushButton("Удалить");
        connect(removeButton, &QPushButton::clicked, [=]() {
            //model->remove(plugins->selectedIndexes().constFirst());
        });

        connect(this, &PluginSettingsPage::modelChanged, model, &PluginHelperListModel::save);

        QPushButton* b2 = new QPushButton("Вверх");
        QPushButton* b3 = new QPushButton("Вниз");
        QHBoxLayout* hbl = new QHBoxLayout();
        hbl->addWidget(removeButton);
        hbl->addWidget(b2);
        hbl->addWidget(b3);
        QWidget *wgt = new QWidget();
        wgt->setLayout(hbl);
        formLayout->addWidget(wgt);
        m_page->setLayout(formLayout);
    }
    return m_page;
}

//model->load();

void PluginSettingsPage::apply()
{
    for(auto &item: tempSettings.toStdMap()) {
        qDebug() << item.first << " : " << item.second;
        settings.setValue(item.first , item.second);
    }

    settings.sync();
    tempSettings.clear();

    emit modelChanged();
}

void PluginSettingsPage::reject() {
    emit restoreSettings();
    tempSettings.clear();
}

QString PluginSettingsPage::displayName() const {
    return m_displayName;
}

QPixmap *PluginSettingsPage::displayIcon() {
    if (!m_icon) {
        m_icon = new QPixmap(":plugins.png");
    }
    return m_icon;
}
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//




//------------------------   IWidgetPage   --------------------------------//
