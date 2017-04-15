#pragma once

#include <QObject>
#include <QApplication>
#include "plugins/pluginhelper.h"

class LTabsApplication : public QApplication
{
    Q_OBJECT

private:

public:
    LTabsApplication(int &argc, char** argv);
    ~LTabsApplication();
    QUuid getUuid();
};

