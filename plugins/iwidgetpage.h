#ifndef IWIDGETPAGE_H
#define IWIDGETPAGE_H

#include <QObject>

class IWidgetPage : public QObject
{
    Q_OBJECT
public:
    explicit IWidgetPage(QObject *parent = 0);

signals:

public slots:
};

#endif // IWIDGETPAGE_H