#pragma once

#include <QtWidgets>

class PluginHelper
{
public:
    PluginHelper():
        uuid(0),
        isActive(false),
        isPrivate(false),
        fileName(QString())
    {  }
    QUuid uuid;
    bool isActive;
    bool isPrivate;
    QString fileName;
};
