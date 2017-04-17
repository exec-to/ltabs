#include "settings/settingsdialog.h"
#include "pluginmanager.h"

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


void SettingsDialog::showDialog() {
    if (!m_instance)
        m_instance = new SettingsDialog();

    m_instance->show();
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


template<typename Fnct>
void for_method(Fnct doAction) {
    for (auto &plugin: PluginManager::pluginsList) {
        ISettingsPage* settings = plugin->getSettingsPage();
        if (settings)
            doAction(settings);
    }
}


void SettingsDialog::accept() {

    for_method([](ISettingsPage* settings) { settings->apply(); });
    this->hide();
}


void SettingsDialog::apply() {

    for_method([](ISettingsPage* settings) { settings->apply(); });
}


void SettingsDialog::reject() {

    this->hide();
    for_method([](ISettingsPage* settings) { settings->reject(); });
}






























