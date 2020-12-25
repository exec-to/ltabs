#pragma once

#include <QObject>
#include <QtPlugin>
#include "iwidgetpage.h"
#include "isettingspage.h"

class IApplicationPlugin
{
protected:
    QUuid m_uuid;
    void setUuid(QUuid uuid) { m_uuid = uuid; }

public:
    QUuid getUuid() { return m_uuid; }

    virtual ~IApplicationPlugin() {  }
    virtual ISettingsPage* getSettingsPage() = 0;
    virtual IWidgetPage* getWidgetPage() = 0;
};

Q_DECLARE_INTERFACE(IApplicationPlugin, "ru.ltabs.plugins.IApplicationPlugin")
