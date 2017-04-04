#pragma once

#include <QObject>
#include <QtWidgets>
#include "settings/isettingspage.h"

class LTabsSettingsGeneralPage : public ISettingsPage
{
    Q_OBJECT

private:
    QWidget* m_page;
    static int count;

public:
    LTabsSettingsGeneralPage();
    QWidget* page(QWidget *parent = 0);

};

