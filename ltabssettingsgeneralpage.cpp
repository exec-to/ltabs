#include "ltabssettingsgeneralpage.h"

LTabsSettingsGeneralPage::LTabsSettingsGeneralPage()
{
    m_displayName = "General";
}

QWidget* LTabsSettingsGeneralPage::page() {
    if (m_page) {
        return m_page;
    }

    m_page = new QLabel("Hello");
    return m_page;
}
