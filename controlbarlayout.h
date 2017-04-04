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
    void createDefaultButtons();


public:
    ControlBarLayout(int btnSize, int appWidth, QWidget* pobj = 0);
    void addWidget(QWidget* pwgt);
    static QPushButton* createControlButton(QString name, int size);

public slots:
    void showSettingsDialog();
};
