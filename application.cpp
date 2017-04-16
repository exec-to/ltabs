#include "application.h"


Application::Application(int &argc, char **argv) : QApplication(argc, argv)
{
    //load plugins
    PluginManager::loadPlugins();

    //set application theme
    //get information about OS etc
}
