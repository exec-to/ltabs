#include "application.h"


Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{
    QCoreApplication::setOrganizationName   ("hprog.ru");
    QCoreApplication::setOrganizationDomain ("hprog.ru");
    QCoreApplication::setApplicationName    ("ltabs"   );

    cfg::Init();
    //load settings
    //initializeSettings();

    //load plugins
    PluginLoader::load();

    //set application style
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QString themeName = cfg::Application::theme_dir() + "/" + cfg::Application::theme();
    QFile themeFile(themeName);
    themeFile.open(QFile::ReadOnly);
    if (themeFile.isOpen()) {
        QString StyleSheet = QLatin1String(themeFile.readAll());
        qApp->setStyleSheet(StyleSheet);
    }

    //get information about OS etc
}


void Application::initializeSettings() {

   /* QSettings settings;

    if (!settings.contains("Application/theme"))
         settings.setValue("Application/theme", "stylesheet.qss");

    //validate!

    if (!settings.contains("Application/icons"))
         settings.setValue("Application/icons", "Light");

    if (!settings.contains("MainWindow/width"))
         settings.setValue("MainWindow/width", 200);

    if (!settings.contains("MainWindow/DockEdge"))
         settings.setValue("MainWindow/DockEdge", "Right");

    if (!settings.contains("ControlButtons/Size"))
         settings.setValue("ControlButtons/Size", 36);

    if (!settings.contains("Application/PluginsDir"))
         settings.setValue("Application/PluginsDir", "./plugins");


    if (!settings.contains("Application/showDesktops"))
         settings.setValue("Application/showDesktops", 2);

    if (!settings.contains("Environment/DefaultDesktop"))
         settings.setValue("Environment/DefaultDesktop", 0);

    if (!settings.contains("Environment/DefaultScreen"))
         settings.setValue("Environment/DefaultScreen", 0);

    if (!settings.contains("Environment/Desktops"))
         settings.setValue("Environment/Desktops", 1);*/
}
