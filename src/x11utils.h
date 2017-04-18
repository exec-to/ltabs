#pragma once

#include <QObject>
#include <QtX11Extras/QtX11Extras>
#include <QtX11Extras/QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

class _net_workarea {
public:
    _net_workarea();
    _net_workarea(unsigned int dx, unsigned int dy, unsigned int w,  unsigned int h);
    unsigned int x;
    unsigned int y;
    unsigned int width;
    unsigned int height;
};

class X11Utils
{

private:
    X11Utils();
    static int getDesktopFreeAreaSize(Display* display, int screen, _net_workarea *wa);

public:
    static _net_workarea initDesktopFreeAreaSize();
    static void setStrut(Window winid, int height, int width, unsigned int start_x, unsigned int start_y, QString dockEdge);
};
