#pragma once
#include <QObject>
#include "pluginmanager.h"
#include "settings/config.h"

class Application : public QApplication
{

public:
    Application(int &argc, char **argv);
};
