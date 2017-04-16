#include "mainboardwidget.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("home");
    QCoreApplication::setOrganizationDomain("ltabs.ru");
    QCoreApplication::setApplicationName("ltabs");

    QApplication app(argc, argv);
    MainBoardWidget w;
    w.show();

    return app.exec();
}
