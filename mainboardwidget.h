#pragma once

#include <QtWidgets>
#include "ltabsapplication.h"
#include "desktoputils.h"
#include "controlbarlayout.h"

class MainBoardWidget : public QWidget
{
    Q_OBJECT

private:
    LTabsApplication* m_app;


public:
    MainBoardWidget(QWidget *parent = 0);
    ~MainBoardWidget();

};

