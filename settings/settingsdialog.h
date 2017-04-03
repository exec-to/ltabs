#pragma once

#include <QObject>
#include <QtWidgets>
#include "settings/isettingspage.h"
#include "settings/settingslistmodel.h"
#include "settings/settingslistwidget.h"

class SettingsDialog : public QDialog
{
    Q_OBJECT

private:
    SettingsDialog(QWidget *parent);
    SettingsListModel* m_model;
    SettingsListWidget* m_settingsList;
    QStackedLayout* m_stackedLayout;
    void setupLayout();
    void currentChanged(const QModelIndex &current);


public:
    static SettingsDialog* getSettingsDialog(QWidget *parent);

};
