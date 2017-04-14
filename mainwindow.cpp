#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QSettings settings;

    //setup main window geometry, position, behavior;
    QRect screen = QApplication::desktop()->geometry();
    //get desktop work area size
    m_desktopGeometry = X11Utils::initDesktopFreeAreaSize();

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

    //setup top layout
    m_tabWidget = new QTabWidget();
    m_tabWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    installPluginWidgets(PluginManager::pluginsList);
    createDefaultButtons();

    QVBoxLayout* topLayout = new QVBoxLayout();
    topLayout->addWidget(m_tabWidget);

    //setup main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(topLayout);
    mainLayout->addWidget(bottomWidget);
    this->setLayout(mainLayout);
    this->setFixedSize(this->size());
}


void MainWindow::createDefaultButtons() {
    QToolButton* btn = m_bottomLayout->createControlButton(QPixmap(":settings.png"));
    connect( btn, &QToolButton::clicked, [=]() {
        SettingsDialog::showDialog();
    });

    btn = m_bottomLayout->createControlButton(QPixmap(":leave.png"));
    connect( btn, &QToolButton::clicked,
         QApplication::instance(),
         &QCoreApplication::quit
    );
}


void MainWindow::show() {

    X11Utils::prepareDesktop
    (
        this->winId(),
        this->height(),
        this->width(),
        m_desktopGeometry.x,
        m_desktopGeometry.y
    );

    QWidget::show();
}


void MainWindow::installPluginWidgets(QList<IApplicationPlugin*> &plugins) {
    for (auto &plugin: plugins) {

        IWidgetPage* widgetPage = plugin->getWidgetPage();
        if (widgetPage) {
            QWidget* w = widgetPage->page();
            m_tabWidget->addTab(w, "tab1");

            QPixmap icon(":1.png"); //plugin->icon;
            QToolButton* btn = m_bottomLayout->createControlButton(icon); //buttom for plugin widget
            connect(btn, &QPushButton::clicked, [=]() {
                m_tabWidget->setCurrentWidget(w);
            });
        }
    }
}


MainWindow::~MainWindow() {

}
