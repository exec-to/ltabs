#pragma once

#include <QObject>
#include <QtWidgets>
#include <QQuickWidget>

#include "iapplicationplugin.h"

class QString;
class QWidget;

//------------------------ GeneralSettings --------------------------------//
class ClipboardPlugin : public QObject, public IApplicationPlugin
{
    Q_OBJECT
    Q_INTERFACES(IApplicationPlugin)
    Q_PLUGIN_METADATA(IID "ru.ltabs.plugins.IApplicationPlugin" FILE "clipboardplugin.json")

protected:
    ISettingsPage* m_settingPage;
    IWidgetPage* m_widgetPage;

public:
    ClipboardPlugin(); // !important! initialize class members
    virtual ~ClipboardPlugin() {  }
    virtual ISettingsPage *getSettingsPage();
    virtual IWidgetPage *getWidgetPage();

};
//------------------------ GeneralSettings --------------------------------//
//------------------------  ISettingsPage  --------------------------------//
class ClipboardPluginSettingsPage: public ISettingsPage {
    Q_OBJECT

private:
    QWidget *m_page;
    QString  m_displayName;

public:
    ClipboardPluginSettingsPage();
    virtual ~ClipboardPluginSettingsPage() {  }
    virtual QWidget* page();
    virtual QString displayName() const;
    virtual QPixmap getIcon();
    virtual void apply();
    virtual void reject();

};
//------------------------  ISettingsPage  --------------------------------//
//------------------------   IWidgetPage   --------------------------------//
class ClipboardPluginWidgetPage: public IWidgetPage {
Q_OBJECT

private:
    QWidget *m_widget;
    QQuickWidget* m_quickWidget;
public:
    ClipboardPluginWidgetPage();
    virtual ~ClipboardPluginWidgetPage() {  }
    virtual QWidget* page();
    virtual QPixmap getIcon();
};



//------------------------   IWidgetPage   --------------------------------//




/*#ifndef CLIPBOARDPLUGIN_H
#define CLIPBOARDPLUGIN_H


class ClipboardPlugin : public IApplicationPlugin
{
public:
    ClipboardPlugin();
};

#endif // CLIPBOARDPLUGIN_H*/
