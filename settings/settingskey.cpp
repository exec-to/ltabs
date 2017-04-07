#include "settingskey.h"

using namespace std;

LocalSettingsKey::LocalSettingsKey(QUuid u, QString k, QString v) :
    m_uuid(u),
    m_key(k),
    m_value(v)
{

}

bool operator<  (const LocalSettingsKey &k1, const LocalSettingsKey &k2)
{
    if (k1.m_uuid == k2.m_uuid)
        return (k1.m_key < k2.m_key);

    return (k1.m_uuid < k2.m_uuid);
}

bool operator== (const LocalSettingsKey &k1, const LocalSettingsKey &k2)
{
    return (k1.m_uuid == k2.m_uuid) && (k1.m_key == k2.m_key);
}

inline QUuid LocalSettingsKey::getUuid() const { return m_uuid; }

inline QString LocalSettingsKey::getKey() const { return m_key; }

inline QString LocalSettingsKey::getValue() const { return m_value; }

//---------------------------------------------------------------------------------------

QList<LocalSettingsKey> LocalSettingsRepository::m_settingsList;

LocalSettingsRepository::LocalSettingsRepository(QObject *parent)
{

}

void LocalSettingsRepository::writeSettings(const QList<LocalSettingsKey> settingsList) {
    m_settingsList = settingsList;
}

QString LocalSettingsRepository::readSettingsKey(QUuid uuid, QString key)
{
    QString value;
    LocalSettingsKey k = LocalSettingsKey(uuid,key,QString());

    QList<LocalSettingsKey>::iterator itr = std::find(m_settingsList.begin(), m_settingsList.end(), k);
    if (itr != m_settingsList.end()) {
        value = itr->getValue();
    }

    return value;
}


QMap<QString, QString> *LocalSettingsRepository::readSettingsKeys(QUuid uuid)
{
    QMap<QString, QString> *keyList = new QMap<QString, QString>();

    QList<LocalSettingsKey>::iterator itr = std::find_if
            (m_settingsList.begin(),
             m_settingsList.end(),
             find_by_uuid(uuid));

    while(itr != m_settingsList.end()) {
        (*keyList)[itr->getKey()] = itr->getValue();
        itr++;
    }

    return keyList;
}















