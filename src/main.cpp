#include "./application.h"
#include "./mainwindow.h"

int main(int argc, char *argv[])
{
    //https://evileg.com/ru/post/147/
    //Qt Single Application

    //https://evileg.com/ru/post/154/
    //app logger

    //https://evileg.com/ru/post/239/
    //theme styles
    //предпочтительнее использовать QSS

    Application app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
