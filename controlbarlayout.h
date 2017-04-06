#pragma once

#include <QObject>
#include <QtWidgets>

class ControlBarLayout : public QGridLayout
{
    Q_OBJECT

private:
    int m_nrows;
    int m_ncolls;
    int m_btnCount;
    int m_buttonSize;



public:
    ControlBarLayout(int btnSize, int appWidth, QWidget* parent);
    void addWidget(QWidget* pwgt);
    QToolButton *createControlButton(const QPixmap icon);

public slots:
    void showSettingsDialog();
    void createDefaultButtons();
};
