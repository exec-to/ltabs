#pragma once
#include <QObject>
#include "pluginmanager.h"
#include "configuration.h"
#include "x11utils.h"

class Application : public QApplication
{

public:
    Application(int &argc, char **argv);
};
