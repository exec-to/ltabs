#include "ltabsapplication.h"

LTabsApplication::LTabsApplication(int &argc, char** argv):
    QApplication(argc, argv),
    m_appSettings(new LTabsSettings()) {
}

LTabsApplication::~LTabsApplication() {
    delete m_appSettings;
    //~QApplication(); ?
}

QString LTabsApplication::readSetting(QUuid uuid, QString key) const {
    //return m_appSettings->getSettingValue(key);
    return LocalSettingsRepository::readSettingsKey(uuid,key);
}

QList<PluginHelper *> LTabsApplication::getPluginsList() {
    return m_appSettings->getPluginsList();
}

QMap<QString, QString> *LTabsApplication::readSettings(QUuid uuid) const
{
    return LocalSettingsRepository::readSettingsKeys(uuid);
}

QUuid LTabsApplication::getUuid() {
    //return QUuid("db507711-94ad-4f54-bffd-1a7789882839");
    m_appSettings->getUuid();
}
