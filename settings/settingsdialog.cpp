#include "settings/settingsdialog.h"
#include "pluginmanager.h"

static QPointer<SettingsDialog> m_instance = 0;

SettingsDialog::SettingsDialog(QWidget* parent):
    QDialog(parent),
    m_model(new SettingsListModel(this)),
    m_settingsList(new SettingsListWidget(this)),
    m_stackedLayout(new QStackedLayout())
{
    m_stackedLayout->addWidget(PluginManager::settingPages.at(0)->page());
    m_model->setPages(PluginManager::settingPages);
    m_settingsList->setModel(m_model);

    connect(m_settingsList->selectionModel(), &QItemSelectionModel::currentRowChanged,
                this, &SettingsDialog::currentChanged);

    setupLayout();
}

void SettingsDialog::currentChanged(const QModelIndex &current)
{
    /*if (current.isValid()) {
        showCategory(m_proxyModel->mapToSource(current).row());
    } else {*/
        m_stackedLayout->setCurrentIndex(0);
        /*m_headerLabel->clear();*/
    //}
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
