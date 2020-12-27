#pragma once

#include <QObject>
#include <QtWidgets>
#include "iapplicationplugin.h"


class SettingsListModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<ISettingsPage*> m_list;

public:
    SettingsListModel(QObject *pobj = 0);
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent = QModelIndex {}) const override;
    void setPages(QList<IApplicationPlugin *> plugins);
    QWidget* getPageByIndex(const QModelIndex &index) const;

};
