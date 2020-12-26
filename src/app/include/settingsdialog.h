#pragma once

#include <QObject>
#include <QtWidgets>
#include "isettingspage.h"
#include "settingslistmodel.h"
#include "settingslistwidget.h"

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
