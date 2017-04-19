#include "application.h"


Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{
    initializeSettings();
    //load plugins
    PluginLoader::load();

    //set application theme
    //get information about OS etc
}


void Application::initializeSettings() {
    QCoreApplication::setOrganizationName("hprog.ru");
    QCoreApplication::setOrganizationDomain("hprog.ru");
    QCoreApplication::setApplicationName("ltabs");

    QSettings settings;
    if (!settings.contains("MainWindow/width"))
        settings.setValue("MainWindow/width", 250);

    if (!settings.contains("MainWindow/DockEdge"))
        settings.setValue("MainWindow/DockEdge", "Right");

    if (!settings.contains("ControlButtons/Size"))
        settings.setValue("ControlButtons/Size", 40);

    if (!settings.contains("Application/PluginsDir"))
        settings.setValue("Application/PluginsDir", "./plugins");


    if (!settings.contains("Application/showDesktops"))
        settings.setValue("Application/showDesktops", 2);

    if (!settings.contains("Environment/DefaultDesktop"))
        settings.setValue("Environment/DefaultDesktop", 0);

    if (!settings.contains("Environment/Desktops"))
        settings.setValue("Environment/Desktops", 1);
}
