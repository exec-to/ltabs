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

 QUuid LTabsSettings::getUuid() const {
    return m_appUuid;
 }


LTabsSettings::LTabsSettings(QObject *pobj):
    m_appUuid(QUuid("db507711-94ad-4f54-bffd-1a7789882839")),
    m_dbSettings(new QSqlDatabase((QSqlDatabase::addDatabase("QSQLITE")))),
    m_localSettings(new QList<LocalSettingsKey>()) {

    if (!openDbConnection())
        qDebug() << "Unknown error";

    if (!(m_dbSettings->tables().size())) {
       //Q_ASSERT(createDatabase());
        createDatabase();
    }

    readSettings();
}

QList<PluginHelper *> LTabsSettings::getPluginsList() {
    return m_pluginsList;
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
     int uuid_index = record.indexOf("uuid");
     int key_index = record.indexOf("setting_key");
     int value_index = record.indexOf("setting_value");


     while(query.next()) {
         QUuid uuid = QUuid(query.value(uuid_index).toString());
         QString key = query.value(key_index).toString();
         QString value = query.value(value_index).toString();
         m_localSettings->append(LocalSettingsKey(uuid,key,value));
         //(*m_localSettings)[key] = value;
     }

     LocalSettingsRepository::writeSettings(*m_localSettings);

     selectString = "SELECT * FROM plugins";
     if (!query.exec(selectString)) {
         qDebug() << "Cannot execute query";
     }

     record = query.record();
     int uuid_col = record.indexOf("uuid");
     int isActive_col = record.indexOf("is_active");
     int isPrivate_col = record.indexOf("is_private");
     int filename_col = record.indexOf("file_name");

     while(query.next()) {
         PluginHelper* ph = new PluginHelper();
         ph->uuid = QUuid(query.value(uuid_col).toString());
         ph->isActive = query.value(isActive_col).toBool();
         ph->isPrivate =query.value(isPrivate_col).toBool();
         ph->fileName = query.value(filename_col).toString();
         m_pluginsList.append(ph);
     }
}

void LTabsSettings::saveSettings(QMap<QString, QString> &tmpSettings) {
    QSqlQuery query;
    //check for exist setting params (exec select count rows => update or insert)

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

    m_dbSettings->setDatabaseName("ltabs_settings.db");
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
            "uuid VARCHAR(37),"
            "setting_key VARCHAR(50), "
            "setting_value VARCHAR(50) "
            ");";

    QSqlQuery query;
    if ( !query.exec(queryString) ) {
        qDebug() << "Unable to create table app_settings";
        return false;
    }

    QString insertString = "INSERT INTO app_settings"
            "(id, uuid, setting_key, setting_value)"
            "VALUES(%1, '%2', '%3', '%4');";
    QString insertRecord;

    int record = 0;
    for( auto &param: defaultSettings().toStdMap() ) {
        insertRecord = insertString.arg(++record)
                .arg(m_appUuid.toString()) //general settings uuid
                .arg(param.first)
                .arg(param.second);


        if( !query.exec(insertRecord) ) {
            qDebug() << "Unable to write data to settings table " << record;
            return false;
        }
    }


    queryString = "CREATE TABLE plugins ( "
            "id INTEGER PRIMARY KEY NOT NULL, "
            "uuid VARCHAR(37)," /*uuid for get plugin settings*/
            "is_active INTEGER, " /*loading plugin when start app*/
            "is_private INTEGER," /*default application plugins (app settings)*/
            "file_name VARCHAR(255) " /*name of plugin file in plugins directory*/
            ");";

    if ( !query.exec(queryString) ) {
        qDebug() << "Unable to create table plugins";
        return false;
    }

    insertString = "INSERT INTO plugins"
                "(id, uuid, is_active, is_private, file_name)"
                "VALUES(%1, '%2', %3, %4, '%5');";

    insertRecord = insertString.arg(1)
            .arg(m_appUuid.toString())
            .arg(1)
            .arg(1)
            .arg("libgeneralsetting.so");

    if( !query.exec(insertRecord) ) {
        qDebug() << "Unable to write data to plugins table";
        return false;
    }


    return true;
}
