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
    virtual void apply() = 0;
    virtual void reject() = 0;
    //virtual void restoreChanges() = 0;

signals:
    void changesRestored();
};

