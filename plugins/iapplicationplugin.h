#pragma once

#include <QObject>
#include <QtPlugin>
#include "iwidgetpage.h"
#include "../settings/isettingspage.h"

class IApplicationPlugin
{

public:
    virtual ~IApplicationPlugin() {  }
    virtual ISettingsPage* getSettingsPage() = 0;
    //virtual IWidgetPage* getWidgetPage() = 0;
};

Q_DECLARE_INTERFACE(IApplicationPlugin, "ru.ltabs.plugins.IApplicationPlugin")
