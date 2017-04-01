#include "mainboardwidget.h"
#include "ltabsapplication.h"

int main(int argc, char *argv[])
{
    LTabsApplication app(argc, argv);
    MainBoardWidget w;

    return app.exec();
}
