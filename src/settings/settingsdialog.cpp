#include "settingsdialog.h"
#include "../pluginmanager.h"

SettingsDialog* SettingsDialog::m_instance = 0;

SettingsDialog::SettingsDialog(QWidget* parent):
    QDialog(parent),
    m_model(new SettingsListModel(this)),
    m_settingsList(new SettingsListWidget(this)),
    m_stackedLayout(new QStackedLayout())
{
    setupLayout();

    m_model->setPages(PluginManager::pluginsList);
    m_settingsList->setModel(m_model);

    connect(m_settingsList->selectionModel(), &QItemSelectionModel::currentRowChanged,
                this, &SettingsDialog::currentChanged);

}


void SettingsDialog::currentChanged(const QModelIndex &current)
{
    if (current.isValid()) {
        QWidget *page = m_model->getPageByIndex(current);

        if (page->parent() != m_stackedLayout) {
            m_stackedLayout->addWidget(page);
        }

        m_stackedLayout->setCurrentWidget(page);

    } else {
        m_stackedLayout->setCurrentIndex(0);
        //m_headerLabel->clear();
    }
}


template<typename Fnct>
void plugins_for(Fnct doAction) {
    for (auto &plugin: PluginManager::pluginsList) {
        ISettingsPage* settings = plugin->getSettingsPage();
        if (settings)
            doAction(settings);
    }
}


void SettingsDialog::showDialog() {
    if (!m_instance)
        m_instance = new SettingsDialog();

    plugins_for([](ISettingsPage* settings) { emit settings->restoreSettings(); });
    m_instance->show();
}


void SettingsDialog::setupLayout() {
    setWindowTitle(tr("Параметры"));
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

    plugins_for([](ISettingsPage* settings) { settings->apply(); });
    this->hide();
}


void SettingsDialog::apply() {

    plugins_for([](ISettingsPage* settings) { settings->apply(); });
}


void SettingsDialog::reject() {

    this->hide();
    plugins_for([](ISettingsPage* settings) { settings->reject(); });
}






























