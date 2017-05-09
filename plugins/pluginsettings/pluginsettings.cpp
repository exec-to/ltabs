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

        QListView *pluginsList = new QListView();
        PluginHelperListModel *model = new PluginHelperListModel();
        pluginsList->setModel(model);

        QPushButton* removeItem = new QPushButton("Удалить");
        connect(removeItem, &QPushButton::clicked, [=]() {
            QModelIndex index = pluginsList->selectionModel()->currentIndex();
            model->remove(index);
        });

        QPushButton* upItem = new QPushButton("Вверх");
        connect(upItem, &QPushButton::clicked, [=]() {
            QModelIndex index = pluginsList->selectionModel()->currentIndex();
            model->moveUp(index);
        });

        QPushButton* downItem = new QPushButton("Вниз");
        connect(downItem, &QPushButton::clicked, [=]() {
            QModelIndex index = pluginsList->selectionModel()->currentIndex();
            model->moveDown(index);
        });

        QLabel *select = new QLabel(tr("Загрузка плагинов:"));

        QPushButton *addItem = new QPushButton("Выбрать...");

        connect(addItem, &QPushButton::clicked, [=]() {
            QString filename = getPluginFileName();
            model->add(filename);
        });

        QTextEdit *description = new QTextEdit("Description");
        description->setReadOnly(true);
        description->setFixedHeight(80);

        /*connect //Обновление текста описания плагина
                  //необходимо разработать данный функционал
        (
            pluginsList->selectionModel(),
            &QItemSelectionModel::currentRowChanged,
            [=](QModelIndex &current) {
                description->setText(current.data(UserRoles::DescriptionRole).toString());
            }
        );*/

        QGridLayout *gridLayout =  new QGridLayout();
         gridLayout->addWidget(     upItem, 0,0,1,1);
         gridLayout->addWidget(   downItem, 1,0,1,1);
         gridLayout->addWidget( removeItem, 2,0,1,1);
         gridLayout->addWidget(pluginsList, 0,1,5,3);
         gridLayout->addWidget(     select, 6,0,1,1);
         gridLayout->addWidget(    addItem, 6,1,1,3);
         gridLayout->addWidget(description, 7,0,1,4);

        m_page->setLayout(gridLayout);
    }
    return m_page;
}

QString PluginSettingsPage::getPluginFileName() {
    QString path = settings
            .value("Application/PluginsDir")
            .toString();

    QDir dir;
    if (!dir.cd(path)) {
        QMessageBox::critical(0,"Error", "Plugins directory does not exist.\nCheck settings configuration.");
        return QString();
    }

    QString filename = QFileDialog::getOpenFileName
    (
        m_page,
        QString("Добавить плагин"),
        dir.absolutePath()
    );

    return filename;
}


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
