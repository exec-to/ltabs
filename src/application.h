#pragma once
#include <QObject>
#include "pluginmanager.h"

class Application : public QApplication
{
private:
    void initializeSettings();

public:
    Application(int &argc, char **argv);
};
