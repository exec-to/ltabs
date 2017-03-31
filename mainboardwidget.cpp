#include "mainboardwidget.h"
#include "ltabsapplication.h"
#include <QtWidgets>
#include "desktoputils.h"

MainBoardWidget::MainBoardWidget(QWidget *parent)
    : QWidget(parent), m_tabBar(new QTabBar),
      ltabsApp(qobject_cast<LTabsApplication*>(LTabsApplication::instance()))
{
    //set geometry for main window
    this->resize(ltabsApp->readSetting("MainWindow/Width"), this->height());


    //setup main window geometry, position, behavior;
    QRect screen = LTabsApplication::desktop()->geometry();
    //get desktop work area size
    QRect desktopFreeArea = DesktopUtils::initDesktopFreeAreaSize();

    QVBoxLayout* mainLayout = new QVBoxLayout();
    //setup top layout
    QVBoxLayout* topLayout = new QVBoxLayout();
    QRect topLayoutGeometry = getTopLayoutGeometry(desktopFreeArea);
    topLayout->setGeometry(topLayoutGeometry);
    topLayout->addWidget(m_tabBar);

    //setup bottom layout
    bottomLayout = new QGridLayout();
    QRect bottomLayoutGeometry = getBottomLayoutGeometry(desktopFreeArea);
    bottomLayout->setGeometry(bottomLayoutGeometry);

    //setup main layout
    mainLayout->addLayout(topLayout);
    mainLayout->addLayout(bottomLayout);
    this->setLayout(mainLayout);
}

MainBoardWidget::~MainBoardWidget() {
    delete m_tabBar;
    delete bottomLayout;
}


//необходимо в данные функции передавать параметры из настроек приложения:
//количество кнопок в нижней части панели
//высота кнопок
QRect MainBoardWidget::getTopLayoutGeometry(QRect screen) {
    QRect r;

    return r;
}

QRect MainBoardWidget::getBottomLayoutGeometry(QRect screen) {
    QRect r;

    return r;
}
