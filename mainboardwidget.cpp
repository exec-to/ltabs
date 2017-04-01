#include "mainboardwidget.h"
#include "ltabsapplication.h"
#include <QtWidgets>
#include "desktoputils.h"
#include "ltabssettingsdialog.h"
#include "controlbarlayout.h"

MainBoardWidget::MainBoardWidget(QWidget *parent)
    : QWidget(parent),
      ltabsApp(qobject_cast<LTabsApplication*>(LTabsApplication::instance()))
{
    int appWidth = ltabsApp->readSetting("MainWindow/Width").toInt();

    //setup main window geometry, position, behavior;
    QRect screen = LTabsApplication::desktop()->geometry();
    //get desktop work area size
    _net_workarea freeArea = DesktopUtils::initDesktopFreeAreaSize();

    setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    this->resize(appWidth, freeArea.height);
    this->move(((ltabsApp->readSetting("MainWindow/DockEdge") == "left") ?
                    screen.left() + freeArea.x :
                    freeArea.width - appWidth),
                    freeArea.y);

    QVBoxLayout* mainLayout = new QVBoxLayout();

    //setup bottom layout
    QWidget *bottomWidget = new QWidget;
    bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    int btnSize = ltabsApp->readSetting("ControlButtons/Size").toInt();

    QTabWidget* m_tabWidget = new QTabWidget();
    ControlBarLayout* bottomLayout = new ControlBarLayout(btnSize, appWidth, bottomWidget);

    //setup top layout
    m_tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    for (int ix = 0; ix < 5; ++ix) { //load plugins here
        QWidget* w = new QWidget();
        m_tabWidget->addTab(w, "tab" + QString::number(ix+1));

        QPushButton* btn = createControlButton("tab" + QString::number(ix+1), btnSize);
        bottomLayout->addWidget(btn);

        QSignalMapper* mapper = new QSignalMapper(this);
        connect(mapper, SIGNAL(mapped(QWidget*)), m_tabWidget, SLOT(setCurrentWidget(QWidget*)));
        connect(btn, SIGNAL(clicked()), mapper, SLOT(map()));
        mapper->setMapping(btn, w);
    }

    QPushButton* pbtn = createControlButton("stngs", btnSize);
    connect( pbtn, SIGNAL(clicked()), SLOT(configureApplicationDialog()) );
    bottomLayout->addWidget(pbtn);
    pbtn = createControlButton("exit", btnSize);
    connect( pbtn, SIGNAL(clicked()), LTabsApplication::instance(), SLOT(quit()) );
    bottomLayout->addWidget(pbtn);


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


QPushButton* MainBoardWidget::createControlButton(QString name, int size) {
    QPushButton* btn = new QPushButton(name);
    btn->setFixedHeight(size);
    btn->setFixedWidth(size);
    return btn;
}


void MainBoardWidget::configureApplicationDialog() {
    LTabsSettingsDialog* pConfigureDialog = new LTabsSettingsDialog();

    if (pConfigureDialog->exec() == QDialog::Accepted) {

    }

    delete pConfigureDialog;
}


MainBoardWidget::~MainBoardWidget() {

}

