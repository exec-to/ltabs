#include "mainboardwidget.h"
#include <QtWidgets>

MainBoardWidget::MainBoardWidget(QWidget *parent)
    : QWidget(parent)
{
    QSettings settings;

    //setup main window geometry, position, behavior;
    QRect screen = QApplication::desktop()->geometry();
    //get desktop work area size
    m_desktopGeometry = DesktopUtils::initDesktopFreeAreaSize();

    setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    int appWidth = settings.value("MainWindow/width", 250).toInt();
    this->resize(appWidth, m_desktopGeometry.height);
    this->move(((settings.value("MainWindow/DockEdge", "right").toString() == "left") ?
                    screen.left() + m_desktopGeometry.x :
                    m_desktopGeometry.width - appWidth),
                    m_desktopGeometry.y);

    //setup bottom layout
    QWidget *bottomWidget = new QWidget;
    bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);
    int btnSize = settings.value("ControlButtons/Size", 40).toInt();
    m_bottomLayout = new ControlBarLayout(btnSize, appWidth, bottomWidget);
    m_bottomLayout->createDefaultButtons();

    //setup top layout
    m_tabWidget = new QTabWidget();
    m_tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    PluginManager::loadPlugins();
    installPluginWidgets(PluginManager::pluginsList);

    QVBoxLayout* topLayout = new QVBoxLayout();
    topLayout->addWidget(m_tabWidget);

    //setup main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(bottomWidget);
    this->setLayout(mainLayout);
    this->setFixedSize(this->size());
}


void MainBoardWidget::show() {
    QWidget::show();
    DesktopUtils::reserveDesktopSpace
    (
        this->winId(),this->height(), this->width(),
        m_desktopGeometry.x, m_desktopGeometry.y
    );
}


void MainBoardWidget::installPluginWidgets(QList<IApplicationPlugin*> &plugins) {
    for (auto &plugin: plugins) {

        IWidgetPage* widgetPage = plugin->getWidgetPage();
        if (widgetPage) {
            QWidget* w = widgetPage->page();
            m_tabWidget->addTab(w, "tab1");

            QPixmap icon(":1.png"); //plugin->icon;
            QToolButton* btn = m_bottomLayout->createControlButton(icon); //buttom for plugin widget
            connect(btn, &QPushButton::clicked, [=]() {
                m_tabWidget->setCornerWidget(w);
            });
        }
    }
}


MainBoardWidget::~MainBoardWidget() {

}

