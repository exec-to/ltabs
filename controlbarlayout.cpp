#include "controlbarlayout.h"

ControlBarLayout::ControlBarLayout(int btnSize, int appWidth, QWidget *pobj): QGridLayout(pobj)
{
    setColumnStretch(0,0);
    setColumnStretch(1,0);
    setAlignment(Qt::AlignRight| Qt::AlignTop);
    setSpacing(0);
    setMargin(0);

    m_btnCount = 0;
    m_nrows = 0;
    m_ncolls = static_cast<int>(appWidth / btnSize);
}


void ControlBarLayout::addWidget(QWidget* pwgt) {
    ++m_btnCount;
    int row = ((m_btnCount % m_ncolls) == 0) ? m_nrows++ : m_nrows;
    int col = ((m_btnCount % m_ncolls) == 0) ? m_ncolls : ((m_btnCount % m_ncolls) - 1);

    QGridLayout::addWidget(pwgt, row, col);
}

