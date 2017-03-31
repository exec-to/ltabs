#pragma once

#include <QtWidgets>
#include "ltabsapplication.h"

class MainBoardWidget : public QWidget
{
    Q_OBJECT

private:
    QTabBar* m_tabBar;
    QGridLayout* bottomLayout;
    LTabsApplication* ltabsApp;

    QRect getTopLayoutGeometry(QRect screen);
    QRect getBottomLayoutGeometry(QRect screen);


public:
    MainBoardWidget(QWidget *parent = 0);
    ~MainBoardWidget();
};

