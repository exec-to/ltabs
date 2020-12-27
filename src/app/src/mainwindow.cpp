#include "mainwindow.h"
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent)
    : QWidget(parent)
{
    setObjectName("mainWindow");

    Qt::WindowFlags flags = Qt::Window
                          | Qt::WindowStaysOnTopHint
                          | Qt::FramelessWindowHint;

    setWindowFlags(flags);
    setWindowOpacity( configuration::UI::opacity() / 100.0 );

    //рабочая область
    m_tabLayout = new QStackedLayout();
    appendPages(m_tabLayout, PluginManager::pluginsList());

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

    QToolButton* btn;

    QString res = ":default.settings.svg";
    btn = createToolButton(QPixmap(res));
    btn->setToolTip(tr("Настройки"));
    connect( btn, &QToolButton::clicked, [=]() {
             SettingsDialog::showDialog();
    });
    m_buttons.append(btn);

    res = ":default.exit.svg";
    btn = createToolButton(QPixmap(res));
    btn->setToolTip(tr("Выход"));
    connect( btn, &QToolButton::clicked,
             QApplication::instance(),
             &QCoreApplication::quit
    );
    m_buttons.append(btn);
}

//задаём настройки WM перед отображением
void MainWindow::show() {

    //полный размер рабочего стола
    QRect screen = QApplication::desktop()->geometry();
    //сторона, к которой нужно прикрепить виджет
    QString position = configuration::Application::position_on_screen();

    //область экрана, доступная для размещения виджета
    m_rect = X11Utils::workarea();

    //ширина виджета
    int  mw_width = configuration::UI::width();
    //доступная высота виджета
    int mw_height = m_rect.height();

    //позиция для размещения
    int      top = m_rect.y();
    int     left = ( position == "left") ? screen.left()  + m_rect.left()
                                     : m_rect.width() + m_rect.left() - mw_width;

    resize(mw_width, mw_height);
    setFixedSize(size());
    move(left, top);

    //геометрия выделенной области
    int strut_width = (position == "right")
            ?  screen.width() - (m_rect.x()  + m_rect.width()) + width()
            : m_rect.x() + width();

    QRect strut_rect(m_rect.x(), m_rect.y(), strut_width, height());
    //выделяем STRUT на рабочем столе для главного виджета
    X11Utils::setStrut( winId(), strut_rect, position );

    //устанавливаем на заданном рабочем столе
    X11Utils::setOnDesktop ( this->winId(), configuration::Application::virtual_desktop() );
    QWidget::show();
}

//получаем виджеты из загруженных плагинов
void MainWindow::appendPages(QStackedLayout *layout, QList<IApplicationPlugin*> plugins) {
    for (auto &plugin: plugins) {
        IWidgetPage* widgetPage = plugin->getWidgetPage();
        if (widgetPage) {
            QWidget*  w = widgetPage->page();
            layout->addWidget(w);
            QToolButton* btn = createToolButton(widgetPage->getIcon());
            connect(btn, &QPushButton::clicked, [=]() {
                layout->setCurrentWidget(w);
            });
            m_buttons.append(btn);
        }
    }
}

//создаём кнопку для области управления
QToolButton* MainWindow::createToolButton(const QPixmap icon) {
    int buttonSize   = configuration::UI::control_buttons_size();

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

