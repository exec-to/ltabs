#pragma once

#include <QtWidgets>
#include "x11utils.h"
#include "controlbarlayout.h"
#include "x11utils.h"
#include "pluginmanager.h"
#include "settings/settingsdialog.h"

class MainWindow : public QWidget
{
    Q_OBJECT

private:
    ControlBarLayout* m_bottomLayout;
     QStackedLayout *m_tabLayout;
    _net_workarea m_desktopGeometry;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void installPluginWidgets(QList<IApplicationPlugin *> plugins);
    void createDefaultButtons();
    void show();
};

