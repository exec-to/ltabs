#pragma once

#include <QObject>
#include <QtWidgets>

class IWidgetPage : public QObject
{
    Q_OBJECT

public:
    virtual ~IWidgetPage() {  }
    virtual QWidget* page() = 0;
    virtual QPixmap displayIcon() = 0;
};
