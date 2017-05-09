#include "mainwindow.h"
#include <QtWidgets>



MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    QSettings settings;
    //setup main window geometry, position, behavior;

    int desktops = X11Utils::getDesktopCount();
    settings.setValue("Environment/Desktops", desktops);

    QRect screen = QApplication::desktop()->geometry();
    //get desktop work area size
    m_desktopGeometry = X11Utils::initDesktopFreeAreaSize();

    setAttribute(Qt::WA_X11NetWmWindowTypeDock);
    setWindowFlags(Qt::Window | Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);

    int appWidth = settings.value("MainWindow/width").toInt();
    this->resize(appWidth, m_desktopGeometry.height);
    this->move(((settings.value("MainWindow/DockEdge").toString() == "Left") ?
                    screen.left() + m_desktopGeometry.x :
                    m_desktopGeometry.width - appWidth),
                    m_desktopGeometry.y);

    this->setObjectName("mainWindow");

    //setup bottom layout
    QWidget *bottomWidget = new QWidget();
    bottomWidget->setObjectName("bottomLayoutWidget");
    bottomWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Minimum);

    m_bottomLayout = new ControlBarLayout(bottomWidget);


    m_tabLayout = new QStackedLayout();

    installPluginWidgets(PluginLoader::pluginsList());
    createDefaultButtons();

    //setup main layout
    QVBoxLayout* mainLayout = new QVBoxLayout();
    mainLayout->addLayout(m_tabLayout);
    mainLayout->addWidget(bottomWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(1,0,1,0);
    this->setLayout(mainLayout);
    this->setFixedSize(this->size());
    //this->layout()->setSpacing(0);

}

void MainWindow::createDefaultButtons() {
    QSettings settings;
    QString iconTheme = settings.value("Application/icons", "Light").toString();
    QToolButton* btn = m_bottomLayout->createControlButton(QPixmap(":" + iconTheme + ".settings.png"));
    connect( btn, &QToolButton::clicked, [=]() {
        SettingsDialog::showDialog();
    });

    btn = m_bottomLayout->createControlButton(QPixmap(":" + iconTheme + ".leave.png"));
    connect( btn, &QToolButton::clicked,
         QApplication::instance(),
         &QCoreApplication::quit
    );
}


void MainWindow::show() {
    QSettings settings;

    X11Utils::setStrut
    (
        this->winId(),
        this->height(),
        this->width(),
        m_desktopGeometry.x,
        m_desktopGeometry.y,
        settings.value("MainWindow/DockEdge").toString()
    );

    int on_all_desktops = settings.value("Application/showDesktops").toInt();
    int defaultDesktop = settings.value("Environment/DefaultDesktop").toInt();

    X11Utils::setOnDesktops
    (
        this->winId(),
        on_all_desktops,
        defaultDesktop
    );

    QWidget::show();
}


void MainWindow::installPluginWidgets(QList<IApplicationPlugin*> plugins) {
    for (auto &plugin: plugins) {

        IWidgetPage* widgetPage = plugin->getWidgetPage();
        if (widgetPage) {
            QWidget* w = widgetPage->page();
            m_tabLayout->addWidget(w);

            QPixmap icon(widgetPage->displayIcon());
            QToolButton* btn = m_bottomLayout->createControlButton(icon); //button for plugin widget
            connect(btn, &QPushButton::clicked, [=]() {
                m_tabLayout->setCurrentWidget(w);
            });
        }
    }
}


MainWindow::~MainWindow() {

}

