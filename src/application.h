#pragma once
#include <QObject>
#include "pluginmanager.h"
#include "settings/config.h"
#include "x11utils.h"

class Application : public QApplication
{

public:
    Application(int &argc, char **argv);
};
