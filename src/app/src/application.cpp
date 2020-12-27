#include "application.h"

Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{
    QCoreApplication::setOrganizationName   ("ltabs");
    QCoreApplication::setOrganizationDomain ("ltabs");
    QCoreApplication::setApplicationName    ("ltabs");

    configuration::Init();

    //load plugins
    PluginManager::load();

    //set application style
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QString themeName = configuration::Application::themes_directory() + "/" + configuration::Application::theme_name();

    QFile   themeFile(themeName);
    themeFile.open(QFile::ReadOnly);
    if (themeFile.isOpen()) {
        QString style = QLatin1String(themeFile.readAll());
        setStyleSheet(style);
    }
}
