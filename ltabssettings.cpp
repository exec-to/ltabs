#include "ltabssettings.h"


QMap<QString, QString> LTabsSettings::defaultSettings() {
    QMap<QString, QString> settings;
    settings["MainWindow/Width"] = "250";
    settings["MainWindow/DockEdge"] = "right";
    settings["Application/PluginsDir"] = "./plugins";
    settings["ControlButtons/Size"] = "40";
    //...
    //return copy of default settings
    return settings;
}

LTabsSettings::LTabsSettings(QObject *pobj):
    m_dbSettings(new QSqlDatabase((QSqlDatabase::addDatabase("QSQLITE")))),
    m_localSettings(new QMap<QString, QString>) {

    if (!openDbConnection())
        qDebug() << "Unknown error";

    //qDebug() << "Existing tables in database: " << m_dbSettings->tables();

    if (!(m_dbSettings->tables().size())) {
       Q_ASSERT(createDatabase());
    }

    readSettings();
}

QString LTabsSettings::getSettingValue(QString &key) const {
    return (*m_localSettings)[key];
}

LTabsSettings::~LTabsSettings() {
    m_dbSettings->close();

    delete m_dbSettings;
    delete m_localSettings;
}

void LTabsSettings::readSettings() {
     QSqlQuery query;
     QString selectString = "SELECT * FROM app_settings";
     if (!query.exec(selectString)) {
         qDebug() << "Cannot execute query";
     }

     QSqlRecord record = query.record();
     int key_index = record.indexOf("setting_key");
     int value_index = record.indexOf("setting_value");

     while(query.next()) {
         QString key = query.value(key_index).toString();
         QString value = query.value(value_index).toString();
         (*m_localSettings)[key] = value;
     }
}

void LTabsSettings::saveSettings(QMap<QString, QString> &tmpSettings) {
    QSqlQuery query;
    QString updateString = "UPDATE app_settings"
            "SET setting_value = '%2'"
            "WHERE setting_key = '%1'";

    QString updateRecord;

    for( auto &param: tmpSettings.toStdMap() ) {
        updateRecord = updateString.arg(param.first)
                .arg(param.second);

        if( !query.exec(updateRecord) ) {
            qDebug() << "Unable to update data in settings table";
        }
    }

}

bool LTabsSettings::openDbConnection() {
    if (!m_dbSettings)
        return false;

    m_dbSettings->setDatabaseName("ltabs_settings");
    m_dbSettings->setUserName("ltabs");
    m_dbSettings->setPassword("password");
    if (!m_dbSettings->open()) {
        qDebug() << "Cannot open database: " << m_dbSettings->lastError();
        return false;
    }
    return m_dbSettings->isOpen();
}

bool LTabsSettings::createDatabase() {

    QString queryString = "CREATE TABLE app_settings ( "
            "id INTEGER PRIMARY KEY NOT NULL, "
            "setting_key VARCHAR(50), "
            "setting_value VARCHAR(50) "
            ");";

    QSqlQuery query;
    if ( !query.exec(queryString) ) {
        qDebug() << "Unable to create table";
        return false;
    }

    QString insertString = "INSERT INTO app_settings"
            "(id, setting_key, setting_value)"
            "VALUES(%1, '%2', '%3');";
    QString insertRecord;

    int record = 0;
    for( auto &param: defaultSettings().toStdMap() ) {
        insertRecord = insertString.arg(++record)
                .arg(param.first)
                .arg(param.second);


        if( !query.exec(insertRecord) ) {
            qDebug() << "Unable to write data to settings table " << record;
            return false;
        }
    }
    return true;
}
