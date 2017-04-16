#pragma once
#include <QObject>
#include "pluginmanager.h"

class Application : public QApplication
{
public:
    Application(int &argc, char **argv);
};
