#pragma once
#include <QObject>
#include <QAbstractListModel>
#include <QSettings>
#include "../../src/plugins/pluginhelper.h"
#include "../../src/plugins/iapplicationplugin.h"

class PluginHelperListModel : public QAbstractListModel
{
    Q_OBJECT

private:
    QList<PluginHelper> m_list;


public:
    PluginHelperListModel();
    QVariant data(const QModelIndex &index, int nRole) const;
    QList<PluginHelper> getPlugins() const;
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex());
    bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex());
    void load();
    void save();

public slots:
    void add(QString &filename);
    void remove(QModelIndex &index);
};
