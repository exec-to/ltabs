#include "mainboardwidget.h"
#include "ltabsapplication.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("home");
    QCoreApplication::setOrganizationDomain("ltabs.ru");
    QCoreApplication::setApplicationName("ltabs");

    LTabsApplication app(argc, argv);
    MainBoardWidget w;

    return app.exec();
}
