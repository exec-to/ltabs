#pragma once

#include <QObject>
#include <QtWidgets>
#include "settings/isettingspage.h"

class LTabsSettingsGeneralPage : public ISettingsPage
{
private:
    QWidget* m_page;

public:
    LTabsSettingsGeneralPage();
    QWidget* page();
};

