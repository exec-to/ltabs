#pragma once

#include <QUuid>
#include <QString>

class PluginHelper
{
public:
    PluginHelper():
        uuid(0),
        isActive(false),
        fileName(QString())
    {  }
    QUuid uuid;
    bool isActive;
    QString fileName;
};
Q_DECLARE_METATYPE(PluginHelper);
