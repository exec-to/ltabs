#pragma once
#include <QMap>
#include <QtSql>
#include "plugins/pluginhelper.h"
#include "settings/settingskey.h"
//#include "ltabsapplication.h"

class LTabsSettings: QObject
{
    Q_OBJECT

private:
    QUuid m_appUuid;
    QList<LocalSettingsKey>* m_localSettings;
    //QMap<QString, QString>* m_localSettings;
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
    //QString getSettingValue(QUuid uuid, QString key) const;
    //QMap<QString,QString> getPluginSettings() const;
    void addSettingKey(QString key, QString value);
    QList<PluginHelper *> getPluginsList();
    QUuid getUuid() const;
};

