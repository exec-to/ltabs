#pragma once

#include <QObject>
#include <QtWidgets>

class ISettingsPage : public QObject
{
    Q_OBJECT

public:
    virtual ~ISettingsPage() { }
    virtual QWidget* page() = 0;
    virtual QString displayName() const = 0;
    virtual QMap<QString, QString> getChangedSettings() = 0;
};

