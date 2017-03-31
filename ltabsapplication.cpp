#include "ltabsapplication.h"

LTabsApplication::LTabsApplication(int &argc, char** argv):
    QApplication(argc, argv),
    m_appSettings(new LTabsSettings()) {

}

LTabsApplication::~LTabsApplication() {
    delete m_appSettings;
    //~QApplication(); ?
}

QString LTabsApplication::readSetting(QString key) const {
    return m_appSettings->getSettingValue(key);
}
