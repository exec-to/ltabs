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
    static Atom NET_WM_STRUT;

public:
    static int getWindowProperty(Atom property, long len, long *buffer);
    static QRect defineWorkarea();
    static void setStrut(Window winid, QRect app_rect, QString app_edge);
    static unsigned int numberOfDesktops();
    static void defineDesktop(Window winid, int all, unsigned int def_desktop);
    static void Init();
};

enum {
    STRUT_LEFT = 0,
    STRUT_RIGHT = 1,
    STRUT_TOP = 2,
    STRUT_BOTTOM = 3,
    STRUT_LEFT_START = 4,
    STRUT_LEFT_END = 5,
    STRUT_RIGHT_START = 6,
    STRUT_RIGHT_END = 7,
    STRUT_TOP_START = 8,
    STRUT_TOP_END = 9,
    STRUT_BOTTOM_START = 10,
    STRUT_BOTTOM_END = 11
};
