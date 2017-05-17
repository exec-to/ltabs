#pragma once

#include <QObject>
//#include <QtX11Extras/QtX11Extras>
//#include <QtX11Extras/QX11Info>
#include <QtCore>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <QX11Info>

class X11Utils
{

private:
    X11Utils() {  }
    //static void* property(int &nitems);
    static Atom NET_WORKAREA;
    static Atom NET_NUMBER_OF_DESKTOPS;
    static Atom NET_WM_WINDOW_TYPE_DOCK;
    static Atom NET_WM_WINDOW_TYPE;
    static Atom NET_WM_DESKTOP;
    static Atom NET_WM_STRUT_PARTIAL;

public:
    static int getWindowProperty(Atom property, long &buffer);
    static QRect availableGeometry();
    static void setStrut(Window winid, int height, int width, unsigned int start_x, unsigned int start_y, QString dockEdge);
    static unsigned int desktopCount();
    static void setOnDesktops(Window winid, int all, unsigned int d);
    static void Init();
};
