#include "application.h"

Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{
    QCoreApplication::setOrganizationName   ("hprog.ru");
    QCoreApplication::setOrganizationDomain ("hprog.ru");
    QCoreApplication::setApplicationName    ("ltabs"   );

    cfg::Init();

    //load plugins
    PluginLoader::load();

    //set application style
    QApplication::setStyle(QStyleFactory::create("Fusion"));

    QString themeName = cfg::Application::theme_dir() + "/" + cfg::Application::theme();
    QFile   themeFile(themeName);
    themeFile.open(QFile::ReadOnly);
    if (themeFile.isOpen()) {
        QString style = QLatin1String(themeFile.readAll());
        setStyleSheet(style);
    }
}
