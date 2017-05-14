#pragma once

#include <QObject>
#include <QtWidgets>
#include "settings/config.h"

class GridControlLayout : public QGridLayout
{
    Q_OBJECT

private:
    int m_nrows;
    int m_ncolls;
    int m_btnCount;
    int m_buttonSize;

public:
    GridControlLayout(QWidget* parent = 0);
    void addWidget   (QWidget* wgt       );
};
