#pragma once

#include <QObject>
#include <QtWidgets>


class LocalSettingsKey
{

private:
    QUuid m_uuid;
    QString m_key;
    QString m_value;

public:
    LocalSettingsKey();
    LocalSettingsKey(QUuid u, QString k, QString v);

    friend bool operator<  (const LocalSettingsKey &k1, const LocalSettingsKey &k2);
    friend bool operator== (const LocalSettingsKey &k1, const LocalSettingsKey &k2);
    inline QUuid getUuid() const;
    inline QString getKey() const;
    inline QString getValue() const;
};


class LocalSettingsRepository: public QObject {

private:
    static QList<LocalSettingsKey> m_settingsList;
    explicit LocalSettingsRepository(QObject *parent = 0);

public:
    static void writeSettings(const QList<LocalSettingsKey> settingsList);
    static QString readSettingsKey(QUuid uuid, QString key);
    static QMap<QString, QString> *readSettingsKeys(QUuid uuid);
};


struct find_by_uuid {
    find_by_uuid(const QUuid & u) : uuid(u) {}
    bool operator()(const LocalSettingsKey & key) {
        return (key.getUuid() == uuid);
    }
private:
    QUuid uuid;
};
