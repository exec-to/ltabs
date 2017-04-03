#pragma once

#include <QObject>
#include "settings/isettingspage.h"

class PluginManager : public QObject
{
    Q_OBJECT
private:
    explicit PluginManager(QObject *parent = 0);
public:
    static QList<ISettingsPage*> settingPages;

};

