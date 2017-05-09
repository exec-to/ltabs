#include "controlbarlayout.h"

ControlBarLayout::ControlBarLayout(QWidget *parent): QGridLayout(parent)
{
    QSettings settings;

    //setColumnStretch(0,0);
    //setColumnStretch(1,0);
    setAlignment(Qt::AlignRight | Qt::AlignTop);
    setSpacing(1);
    setMargin(1);

    int appWidth = settings.value("MainWindow/width").toInt();
    m_btnCount = 0;
    m_nrows = 0;
    m_buttonSize = settings.value("ControlButtons/Size").toInt();
    m_ncolls = static_cast<int>(appWidth / m_buttonSize);
}

void ControlBarLayout::addWidget(QWidget* pwgt) {
    ++m_btnCount; //calculate button position on grid layout
    int row = ((m_btnCount % m_ncolls) == 0) ? m_nrows++ : m_nrows;
    int col = ((m_btnCount % m_ncolls) == 0) ? m_ncolls  : ((m_btnCount % m_ncolls) - 1);

    QGridLayout::addWidget(pwgt, row, col);
}

QToolButton* ControlBarLayout::createControlButton(const QPixmap icon) {
    QToolButton* btn = new QToolButton();
    btn->setFixedHeight(m_buttonSize);
    btn->setFixedWidth(m_buttonSize);
    btn->setAutoRaise(true);
    btn->setIcon(icon);
    btn->setIconSize(QSize(m_buttonSize-2,m_buttonSize-2));
    //btn->setStyleSheet("QToolButton:hover {background-color:lightblue} QToolButton:!hover {background-color:lightgray}");
    this->addWidget(btn);
    return btn;
}
