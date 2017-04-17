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
    ControlBarLayout(QWidget* parent);
    void addWidget(QWidget* pwgt);
    QToolButton *createControlButton(const QPixmap icon);

};
