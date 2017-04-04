#include "settings/settingsdialog.h"
#include "pluginmanager.h"
#include "settings/isettingspage.h"
#include "ltabssettingsgeneralpage.h"

static SettingsDialog* m_instance = 0;

SettingsDialog::SettingsDialog(QWidget* parent):
    QDialog(parent),
    m_model(new SettingsListModel(this)),
    m_settingsList(new SettingsListWidget(this)),
    m_stackedLayout(new QStackedLayout())
{
    createDefaultSettingsItems();

    //need to find by index
    ISettingsPage* generalPage = PluginManager::settingPages.at(0);
    QWidget* gpage = generalPage->page(this);

    ISettingsPage* advancedPage = PluginManager::settingPages.at(1);
    QWidget* apage = advancedPage->page(this);

    m_model->setPages(PluginManager::settingPages);
    m_settingsList->setModel(m_model);

    connect(m_settingsList->selectionModel(), &QItemSelectionModel::currentRowChanged,
                this, &SettingsDialog::currentChanged);

    setupLayout();

    m_stackedLayout->addWidget(gpage);
    m_stackedLayout->addWidget(apage);
}

void SettingsDialog::currentChanged(const QModelIndex &current)
{

    if (current.isValid()) {
        int i = current.data(UserRoles::TabWidgetRole).toInt();
        m_stackedLayout->setCurrentIndex(i);
    } else {
        m_stackedLayout->setCurrentIndex(0);
        //m_headerLabel->clear();
    }
}

void SettingsDialog::createDefaultSettingsItems() {

    LTabsSettingsGeneralPage* generalSettings = new LTabsSettingsGeneralPage();
    PluginManager::settingPages.append(generalSettings);
    LTabsSettingsGeneralPage* advancedSettings = new LTabsSettingsGeneralPage();
    PluginManager::settingPages.append(advancedSettings);

}

SettingsDialog* SettingsDialog::getSettingsDialog(QWidget *parent) {
    if (!m_instance)
        m_instance = new SettingsDialog(parent);

    return m_instance;
}

void SettingsDialog::setupLayout() {
    this->resize(600, 400);

    QGridLayout* gridLayout = new QGridLayout();
    gridLayout->addWidget(m_settingsList, 0, 0);
    gridLayout->addLayout(m_stackedLayout,0, 1);

    this->setLayout(gridLayout);
}
