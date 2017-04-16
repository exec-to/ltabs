#pragma once

#include <QtWidgets>
#include "desktoputils.h"
#include "controlbarlayout.h"
#include "desktoputils.h"
#include "pluginmanager.h"

class MainBoardWidget : public QWidget
{
    Q_OBJECT

private:
    ControlBarLayout* m_bottomLayout;
    QTabWidget* m_tabWidget;
    _net_workarea m_desktopGeometry;

public:
    MainBoardWidget(QWidget *parent = 0);
    ~MainBoardWidget();
    void installPluginWidgets(QList<IApplicationPlugin*> &plugins);
    void show();

};

