#include "mainwindow.h"
#include "application.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("hprog.ru");
    QCoreApplication::setOrganizationDomain("hprog.ru");
    QCoreApplication::setApplicationName("ltabs");

    Application app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
