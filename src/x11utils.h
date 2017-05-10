#pragma once

#include <QObject>
#include <QtX11Extras/QtX11Extras>
#include <QtX11Extras/QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>
#include <QX11Info>

class X11Utils
{

private:
    X11Utils();
    static int getDesktopFreeAreaSize(Display* display, int screen, QRect *wa);
    static void* property(Window win, Atom prop, Atom type, int &nitems);

public:
    static QRect availableGeometry(int screen = 0);
    static void setStrut(Window winid, int height, int width, unsigned int start_x, unsigned int start_y, QString dockEdge);
    static unsigned int desktopCount();
    static void setOnDesktops(Window winid, int all, unsigned int d);
};
