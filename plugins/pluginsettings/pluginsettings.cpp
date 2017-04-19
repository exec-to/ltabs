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
        formLayout->addRow(tr("&Загрузка плагинов:"), new QPushButton("Выбрать..."));
        QListWidget* plugins = new QListWidget();
        /*QList<PluginHelper> *plist = loadList();

        for (PluginHelper &item: plist) {
            plugins->addItem(item.fileName);
        }*/

        formLayout->addWidget(plugins);

        QPushButton* b1 = new QPushButton("Удалить");
        QPushButton* b2 = new QPushButton("Вверх");
        QPushButton* b3 = new QPushButton("Вниз");
        QHBoxLayout* hbl = new QHBoxLayout();
        hbl->addWidget(b1);
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
/*QList<PluginHelper> *loadList() {
    QList<PluginHelper> *list = new QList<PluginHelper>();
    int size = settings.beginReadArray("enabled_plugins");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);
        PluginHelper plugin;
        plugin.uuid = QUuid(settings.value("uuid").toString());
        plugin.fileName = settings.value("fileName").toString();
        plugin.isActive = settings.value("isActive").toBool();
        plugin.isPrivate = settings.value("isPrivate").toBool();
        list->append(plugin);
    }
    settings.endArray();
    return list;
}*/


void PluginSettingsPage::apply()
{
    for(auto &item: tempSettings.toStdMap()) {
        qDebug() << item.first << " : " << item.second;
        settings.setValue(item.first , item.second);
    }

    settings.sync();
    tempSettings.clear();
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
