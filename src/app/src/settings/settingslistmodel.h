#pragma once

#include <QObject>
#include <QtWidgets>
#include "../../../include/iapplicationplugin.h"


class SettingsListModel : public QAbstractListModel
{
    Q_OBJECT
private:
    QList<ISettingsPage*> m_list;

public:
    SettingsListModel(QObject *pobj = 0);
    QVariant data(const QModelIndex &index, int role) const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    void setPages(QList<IApplicationPlugin *> plugins);
    QWidget* getPageByIndex(const QModelIndex &index) const;

};
