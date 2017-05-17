#pragma once

#include <QUuid>
#include <QString>

class PluginHelper
{
public:
    PluginHelper( ): PluginHelper(0,QString()) {  }
    PluginHelper(QString u, QString f): uuid(u), fileName(f) {  }

    QUuid uuid;
    QString fileName;

    bool operator== (PluginHelper helper) {
        return (uuid == helper.uuid);
    }
};
Q_DECLARE_METATYPE(PluginHelper);
