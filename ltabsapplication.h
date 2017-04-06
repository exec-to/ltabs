#pragma once

#include <QObject>
#include <QApplication>
#include "ltabssettings.h"
#include "plugins/pluginhelper.h"

class LTabsApplication : public QApplication
{
    Q_OBJECT

private:
    LTabsSettings* m_appSettings;


public:
    LTabsApplication(int &argc, char** argv);
    ~LTabsApplication();
    QString readSetting(QString key) const;
    QList<PluginHelper *> getPluginsList();
};

