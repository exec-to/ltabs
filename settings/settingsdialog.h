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
    static SettingsDialog* m_instance;
    SettingsDialog(QWidget *parent = 0);
    SettingsListModel* m_model;
    SettingsListWidget* m_settingsList;
    QStackedLayout* m_stackedLayout;
    void setupLayout();
    void currentChanged(const QModelIndex &current);
    void accept();
    void reject();
    void apply();

public:
    static void showDialog();

};
