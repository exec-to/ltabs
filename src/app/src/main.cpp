#include "application.h"
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //https://evileg.com/ru/post/147/
    //Qt Single Application

    //https://evileg.com/ru/post/154/
    //app logger

    //TODO:
    //Выбор действия при нажатии на кнопку
    //убрать ненужные заголовки

    Application app(argc, argv);
    MainWindow w;
    w.show();

    return app.exec();
}
