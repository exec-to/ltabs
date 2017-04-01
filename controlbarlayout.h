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

    //QPushButton* addControlButton(QString text, int size, bool isStaticControl = false);
    //QPushButton *placementControlButton(QString name, int buttonSize, int grid_x, int grid_y, bool isStaticControl = false);
    //QWidget* setupBottomLayout();

public:
    ControlBarLayout(int btnSize, int appWidth, QWidget* pobj = 0);
    void addWidget(QWidget* pwgt);


};
