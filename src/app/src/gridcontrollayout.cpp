#include "gridcontrollayout.h"

GridControlLayout::GridControlLayout(QWidget *parent): QGridLayout(parent)
{
    setAlignment  (Qt::AlignRight | Qt::AlignTop);
    setSpacing    (1);
    setMargin     (1);

    m_btnCount   = 0;
    m_nrows      = 0;
    int appWidth = cfg::MainWindow::width();
    m_buttonSize = cfg::MainWindow::button_size();
    m_ncolls     = static_cast<int>(appWidth / m_buttonSize);
}

//calculate button position before added
void GridControlLayout::addWidget(QWidget* wgt) {
    m_buttons.append(static_cast<QToolButton *>(wgt));

    int pos = ++m_btnCount % m_ncolls;
    int row = !pos ? m_nrows++ : m_nrows;
    int col = !pos ? m_ncolls  : pos - 1;

    QGridLayout::addWidget(wgt, row, col);
}
