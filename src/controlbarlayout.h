#pragma once

#include <QObject>
#include <QtWidgets>

class ControlBarLayout : public QGridLayout
{
    Q_OBJECT

private:
    int m_nrows;
    int m_ncolls;
    int m_btnCount;
    int m_buttonSize;

public:
    ControlBarLayout(QWidget* parent = 0);
    void addWidget(QWidget* pwgt);
};
