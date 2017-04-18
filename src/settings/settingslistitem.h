#pragma once

#include <QObject>
#include <QtWidgets>
#include "../plugins/isettingspage.h"

class SettingsListItem : public QObject
{
    Q_OBJECT

private:
    ISettingsPage* m_page;
    QString m_displayName;
    QWidget *m_widget;
    QIcon m_icon;


public:
    explicit SettingsListItem(ISettingsPage* page, QObject *parent = 0);
    QString displayName() const;
    QWidget* widget() const;
    QIcon icon();
};
