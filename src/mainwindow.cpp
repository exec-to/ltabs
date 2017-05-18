#include "mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{

    cfg::Environment::dt_num(X11Utils::numberOfDesktops());

    setObjectName("mainWindow");

    Qt::WindowFlags flags = Qt::Window
                          | Qt::WindowStaysOnTopHint
                          | Qt::FramelessWindowHint;
    setWindowFlags(flags);


    //область экрана, доступная для размещения виджета
          m_rect = X11Utils::defineWorkarea();
    //ширина виджета
    int    width = cfg::MainWindow::width();
    //доступная высота виджета
    int   height = m_rect.height();
    //полный размер рабочего стола
    QRect screen = QApplication::desktop()->geometry();
    //сторона, к которой нужно прикрепить виджет
    QString edge = cfg::MainWindow::edge();
    //позиция для перемещения
    int      top = m_rect.y();
    int     left = ( edge == "left") ? screen.left()  + m_rect.x()
                                     : m_rect.width() + m_rect.x() - width;
    resize(width, height);
    setFixedSize(size());
    move(left, top);

    //рабочая область
    m_tabLayout       = new QStackedLayout();
    appendPages(PluginLoader::pluginsList());

    //область управления программой
    QWidget *bottomWidget = new QWidget();
             bottomWidget->setObjectName("bottomLayoutWidget");
             bottomWidget->setSizePolicy(QSizePolicy::Expanding,
                                         QSizePolicy::Minimum);

    m_bottomLayout = new GridControlLayout(bottomWidget);

    createDefaultButtons();
    for (auto &b: m_buttons) {
        m_bottomLayout->addWidget(b);
    }

    //компоновка главного виджета
    QVBoxLayout* mainLayout = new QVBoxLayout();
                 mainLayout->addLayout(m_tabLayout);
                 mainLayout->addWidget(bottomWidget);
                 mainLayout->setSpacing(0);
                 mainLayout->setContentsMargins(1,0,1,0);
    setLayout(   mainLayout);
}

//статические кнопки для области управления
void MainWindow::createDefaultButtons() {

    QString iconTheme = cfg::Application::icons_set();
    QToolButton* btn;

    //диалоговое окно настроек
    QString res = ":" + iconTheme + ".settings.png";
    btn = createToolButton(QPixmap(res));
    connect( btn, &QToolButton::clicked, [=]() {
             SettingsDialog::showDialog();
    });
    m_buttons.append(btn);

    //завершение работы программы
    res = ":" + iconTheme + ".leave.png";
    btn = createToolButton(QPixmap(res));
    connect( btn, &QToolButton::clicked,
             QApplication::instance(),
             &QCoreApplication::quit
    );
    m_buttons.append(btn);
}

//задаём настройки WM перед отображением
void MainWindow::show() {

    //QRect app_rect(m_rect.x(), m_rect.y(), width(), height());
    QRect screen_rect = QApplication::desktop()->geometry();

    int strut_width = (cfg::MainWindow::edge() == "right")
            ?  screen_rect.width() - (m_rect.x()  + m_rect.width()) + width()
            : width();

    QRect strut_rect(m_rect.x(), m_rect.y(), strut_width, height());
    //выделяем STRUT на рабочем столе для главного виджета
    X11Utils::setStrut( winId(), strut_rect, cfg::MainWindow::edge() );

    //устанавливаем на заданном рабочем столе
    X11Utils::defineDesktop
    (
        this->winId(),
        cfg::Environment::is_dock(),
        cfg::Environment::def_dt()
    );

    QWidget::show();
}

//получаем виджеты из загруженных плагинов
void MainWindow::appendPages(QList<IApplicationPlugin*> plugins) {
    for (auto &plugin: plugins) {
        IWidgetPage* widgetPage = plugin->getWidgetPage();
        if (widgetPage) {
            QWidget*  w = widgetPage->page();
            m_tabLayout->addWidget(w);
            QToolButton* btn = createToolButton(widgetPage->displayIcon());
            connect(btn, &QPushButton::clicked, [=]() {
                m_tabLayout->setCurrentWidget(w);
            });
            m_buttons.append(btn);
        }
    }
}

//создаём кнопку для области управления
QToolButton* MainWindow::createToolButton(const QPixmap icon) {
    int buttonSize   = cfg::MainWindow::button_size();

    QToolButton* btn = new QToolButton();
    btn->setFixedHeight    (buttonSize);
    btn->setFixedWidth     (buttonSize);
    btn->setAutoRaise      (true);
    btn->setIcon           (icon);
    btn->setIconSize       (QSize(buttonSize-2,buttonSize-2));
    return btn;
}


MainWindow::~MainWindow() {

}

