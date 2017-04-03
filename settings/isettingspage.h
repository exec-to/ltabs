#pragma once

#include <QObject>
#include <QtWidgets>

class ISettingsPage : public QObject
{
    Q_OBJECT

protected:
    QString m_displayName;

public:
    explicit ISettingsPage(QObject *parent = 0);
    virtual QWidget* page() = 0;
    QString displayName() const;
    QIcon icon;
};

