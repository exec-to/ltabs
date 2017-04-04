#pragma once

#include <QObject>
#include <QtWidgets>
#include "settings/isettingspage.h"

class SettingsListItem : public QObject
{
    Q_OBJECT

private:
    ISettingsPage* m_page;
    QString m_displayName;
    QWidget *m_Widget;

public:
    explicit SettingsListItem(ISettingsPage* page, QObject *parent = 0);
    QString displayName() const;
    QWidget* widget() const;
    QIcon icon;
};
