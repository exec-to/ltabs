#include "controlbarlayout.h"
#include "ltabsapplication.h"
#include "settings/settingsdialog.h"

ControlBarLayout::ControlBarLayout(int btnSize, int appWidth, QWidget *pobj): QGridLayout(pobj)
{
    setColumnStretch(0,0);
    setColumnStretch(1,0);
    setAlignment(Qt::AlignRight| Qt::AlignTop);
    setSpacing(1);
    setMargin(1);

    m_btnCount = 0;
    m_nrows = 0;
    m_buttonSize = btnSize;
    m_ncolls = static_cast<int>(appWidth / btnSize);



}


void ControlBarLayout::addWidget(QWidget* pwgt) {
    ++m_btnCount;
    int row = ((m_btnCount % m_ncolls) == 0) ? m_nrows++ : m_nrows;
    int col = ((m_btnCount % m_ncolls) == 0) ? m_ncolls : ((m_btnCount % m_ncolls) - 1);

    QGridLayout::addWidget(pwgt, row, col);
}


void ControlBarLayout::createDefaultButtons() {
    QToolButton* pbtn = createControlButton(QPixmap(":settings.png"));

    connect( pbtn, SIGNAL(clicked()), this, SLOT(showSettingsDialog()) );

    pbtn = createControlButton(QPixmap(":leave.png"));

    connect( pbtn, SIGNAL(clicked()), LTabsApplication::instance(), SLOT(quit()) );
}


void ControlBarLayout::showSettingsDialog() {

    SettingsDialog* pConfigureDialog = SettingsDialog::getSettingsDialog();
    pConfigureDialog->show();

}

QToolButton* ControlBarLayout::createControlButton(const QPixmap icon) {
    QToolButton* btn = new QToolButton();

    btn->setFixedHeight(m_buttonSize);
    btn->setFixedWidth(m_buttonSize);
    btn->setAutoRaise(true);

    btn->setIcon(icon);
    btn->setIconSize(QSize(m_buttonSize-8,m_buttonSize-8));

    btn->setStyleSheet("QToolButton:hover {background-color:lightblue} QToolButton:!hover {background-color:lightgray}");

    this->addWidget(btn);

    return btn;
}
