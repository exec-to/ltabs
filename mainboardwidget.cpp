#include "mainboardwidget.h"
#include "ltabsapplication.h"
#include <QtWidgets>
#include "desktoputils.h"
#include "settings/settingsdialog.h"
#include "settings/settingslistitem.h"
#include "settings/settingslistmodel.h"
#include "controlbarlayout.h"
#include "pluginmanager.h"

MainBoardWidget::MainBoardWidget(QWidget *parent)
    : QWidget(parent),
      m_app(qobject_cast<LTabsApplication*>(LTabsApplication::instance()))
{
    int appWidth = m_app->readSetting("MainWindow/Width").toInt();

    //setup main window geometry, position, behavior;
    QRect screen = LTabsApplication::desktop()->geometry();
    //get desktop work area size
    _net_workarea freeArea = DesktopUtils::initDesktopFreeAreaSize();

    setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    this->resize(appWidth, freeArea.height);
    this->move(((m_app->readSetting("MainWindow/DockEdge") == "left") ?
                    screen.left() + freeArea.x :
                    freeArea.width - appWidth),
                    freeArea.y);

    QVBoxLayout* mainLayout = new QVBoxLayout();

    //setup bottom layout
    QWidget *bottomWidget = new QWidget;
    bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    int btnSize = m_app->readSetting("ControlButtons/Size").toInt();

    QTabWidget* m_tabWidget = new QTabWidget();
    ControlBarLayout* bottomLayout = new ControlBarLayout(btnSize, appWidth, bottomWidget);

    //setup top layout
    m_tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    PluginManager::LoadPlugins(m_tabWidget, bottomLayout);

    bottomLayout->createDefaultButtons();

    QVBoxLayout* topLayout = new QVBoxLayout();
    topLayout->addWidget(m_tabWidget);


    //setup main layout
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(bottomWidget);
    this->setLayout(mainLayout);

    this->show();
    DesktopUtils::reserveDesktopSpace(this->winId(),
                                      this->height(), this->width(),
                                      freeArea.x, freeArea.y);
}



MainBoardWidget::~MainBoardWidget() {

}

