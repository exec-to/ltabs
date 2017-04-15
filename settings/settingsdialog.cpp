#include "settings/settingsdialog.h"
#include "pluginmanager.h"
#include "settings/isettingspage.h"

static SettingsDialog* m_instance = 0;

SettingsDialog::SettingsDialog(QWidget* parent):
    QDialog(parent),
    m_model(new SettingsListModel(this)),
    m_settingsList(new SettingsListWidget(this)),
    m_stackedLayout(new QStackedLayout())
{
    setupLayout();

    //need to find by index
    ISettingsPage* generalPage = PluginManager::settingPages.first();
    QWidget* gpage = generalPage->page();

    //add plugins settings here

    m_model->setPages(PluginManager::settingPages);
    m_settingsList->setModel(m_model);

    connect(m_settingsList->selectionModel(), &QItemSelectionModel::currentRowChanged,
                this, &SettingsDialog::currentChanged);

    m_stackedLayout->addWidget(gpage);

}

void SettingsDialog::currentChanged(const QModelIndex &current)
{
    if (current.isValid()) {
        QWidget *page = m_model->getPageByIndex(current);
        if (page->parent() == m_stackedLayout) {
            m_stackedLayout->setCurrentWidget(page);
        }
    } else {
        m_stackedLayout->setCurrentIndex(0);
        //m_headerLabel->clear();
    }
}


SettingsDialog* SettingsDialog::getSettingsDialog(QWidget *parent) {
    if (!m_instance)
        m_instance = new SettingsDialog(parent);

    return m_instance;
}

void SettingsDialog::setupLayout() {
    this->resize(600, 400);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(m_settingsList, 0, 0, 1, 1);
    gridLayout->addLayout(m_stackedLayout,0, 1, 1, 1);

    QDialogButtonBox *buttonBox = new QDialogButtonBox(
                QDialogButtonBox::Ok |
                QDialogButtonBox::Apply |
                QDialogButtonBox::Cancel);

    connect(buttonBox->button(QDialogButtonBox::Apply),
            &QAbstractButton::clicked,
            this, &SettingsDialog::apply);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &SettingsDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &SettingsDialog::reject);


    gridLayout->addWidget(buttonBox, 1,0,1,2);

    this->setLayout(gridLayout);

    buttonBox->button(QDialogButtonBox::Ok)->setDefault(true);
}

void SettingsDialog::accept() {
    //QMap<QString, QString> settings =
     //       PluginManager::settingPages.first()->getChangedSettings();
    //((LTabsApplication*)LTabsApplication::instance())->saveSettings(settings);
    PluginManager::settingPages.first()->apply();
    this->hide();
}

void SettingsDialog::apply() {

    //QMap<QString, QString> settings =
            //PluginManager::settingPages.first()->getChangedSettings();
    //((LTabsApplication*)LTabsApplication::instance())->saveSettings(settings);

    PluginManager::settingPages.first()->apply();
}

void SettingsDialog::reject() {
    this->hide();
    emit PluginManager::settingPages.first()->reject();
}






























