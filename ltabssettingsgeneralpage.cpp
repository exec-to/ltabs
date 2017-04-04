#include "ltabssettingsgeneralpage.h"

int LTabsSettingsGeneralPage::count = 0;

LTabsSettingsGeneralPage::LTabsSettingsGeneralPage():
    ISettingsPage(),
    m_page(nullptr)
{

    m_displayName = "General " + QString::number(++count);
}

QWidget* LTabsSettingsGeneralPage::page( QWidget* parent) {
    if (!m_page) {
        m_page = new QLabel("Holla yoba! " + QString::number(++count));
    }

    return m_page;
}

