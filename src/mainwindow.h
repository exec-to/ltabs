#pragma once

#include <QtWidgets>
#include "x11utils.h"
#include "gridcontrollayout.h"
#include "pluginmanager.h"
#include "settings/settingsdialog.h"
#include "settings/config.h"


class MainWindow : public QWidget
{
    Q_OBJECT

private:
    GridControlLayout    *m_bottomLayout;
    QStackedLayout       *m_tabLayout;
    QList<QToolButton *>  m_buttons;
    QRect                 m_rect;

public:
                          MainWindow(QWidget *parent = 0);
                          ~MainWindow();
    void                  appendPages(QList<IApplicationPlugin *> plugins);
    void                  createDefaultButtons();
    QToolButton*          createToolButton(const QPixmap icon);
    void                  show();
};

