#pragma once

#include <QObject>
#include <QtCore>
#include <X11/Xutil.h>
#include <kwindowsystem.h>

class X11Utils
{

private:
    X11Utils() {  }
    static Atom NET_WORKAREA;
    static Atom NET_NUMBER_OF_DESKTOPS;
    static Atom NET_WM_WINDOW_TYPE_DOCK;
    static Atom NET_WM_WINDOW_TYPE;
    static Atom NET_WM_DESKTOP;
    static Atom NET_WM_STRUT_PARTIAL;
    static Atom NET_WM_STRUT;

public:
    static QRect defineWorkarea();
    static void setStrut(Window winid, QRect app_rect, QString orient);
    static unsigned int numberOfDesktops();
    static void defineDesktop(Window winid, int all, unsigned int def_desktop);
};
