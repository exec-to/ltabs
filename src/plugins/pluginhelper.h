#pragma once

#include <QUuid>
#include <QString>

class PluginHelper
{
public:
    PluginHelper():
        uuid(0),
        fileName(QString())
    {  }
    QUuid uuid;
    QString fileName;

    bool operator== (PluginHelper helper) {
        return (uuid == helper.uuid);
    }
};
Q_DECLARE_METATYPE(PluginHelper);
