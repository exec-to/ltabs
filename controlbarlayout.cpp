#include "controlbarlayout.h"
#include "ltabsapplication.h"
#include "settings/settingsdialog.h"

ControlBarLayout::ControlBarLayout(int btnSize, int appWidth, QWidget *pobj): QGridLayout(pobj)
{
    setColumnStretch(0,0);
    setColumnStretch(1,0);
    setAlignment(Qt::AlignRight| Qt::AlignTop);
    setSpacing(0);
    setMargin(0);

    m_btnCount = 0;
    m_nrows = 0;
    m_buttonSize = btnSize;
    m_ncolls = static_cast<int>(appWidth / btnSize);

    createDefaultButtons();

}


void ControlBarLayout::addWidget(QWidget* pwgt) {
    ++m_btnCount;
    int row = ((m_btnCount % m_ncolls) == 0) ? m_nrows++ : m_nrows;
    int col = ((m_btnCount % m_ncolls) == 0) ? m_ncolls : ((m_btnCount % m_ncolls) - 1);

    QGridLayout::addWidget(pwgt, row, col);
}


void ControlBarLayout::createDefaultButtons() {
    QPushButton* pbtn = createControlButton("stngs", m_buttonSize);
    connect( pbtn, SIGNAL(clicked()), this, SLOT(showSettingsDialog()) );
    this->addWidget(pbtn);
    pbtn = createControlButton("exit", m_buttonSize);
    connect( pbtn, SIGNAL(clicked()), LTabsApplication::instance(), SLOT(quit()) );
    this->addWidget(pbtn);
}


void ControlBarLayout::showSettingsDialog() {

    SettingsDialog* pConfigureDialog = SettingsDialog::getSettingsDialog();
    pConfigureDialog->show();

}

QPushButton* ControlBarLayout::createControlButton(QString name, int size) {
    QPushButton* btn = new QPushButton(name);
    btn->setFixedHeight(size);
    btn->setFixedWidth(size);
    return btn;
}
