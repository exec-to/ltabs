#include "isettingspage.h"

ISettingsPage::ISettingsPage(QObject *parent) : QObject(parent)
{

}

QString ISettingsPage::displayName() const {
    return m_displayName;
}
