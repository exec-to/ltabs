#pragma once
#include <QMap>
#include <QtSql>
#include "plugins/pluginhelper.h"

class LTabsSettings: QObject
{
    Q_OBJECT

private:
    QMap<QString, QString>* m_localSettings;
    QSqlDatabase* m_dbSettings;
    QList<PluginHelper *> m_pluginsList;

    //DDL
    bool createDatabase();
    bool openDbConnection();

public:
    LTabsSettings(QObject *pobj = 0);
    ~LTabsSettings();
    void readSettings();
    void saveSettings(QMap<QString, QString> &tmpSettings);
    static QMap<QString, QString> defaultSettings();
    QString getSettingValue(QString &key) const;
    void addSettingKey(QString key, QString value);
    QList<PluginHelper *> getPluginsList();
};

