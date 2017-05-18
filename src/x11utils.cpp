#include "x11utils.h"

Atom X11Utils::NET_WORKAREA            = 0;
Atom X11Utils::NET_WM_STRUT            = 0;
Atom X11Utils::NET_WM_DESKTOP          = 0;
Atom X11Utils::NET_WM_WINDOW_TYPE      = 0;
Atom X11Utils::NET_WM_STRUT_PARTIAL    = 0;
Atom X11Utils::NET_NUMBER_OF_DESKTOPS  = 0;
Atom X11Utils::NET_WM_WINDOW_TYPE_DOCK = 0;


void X11Utils::Init() {
    Display *display = QX11Info::display();

    NET_WORKAREA            = XInternAtom(display, "_NET_WORKAREA",            False);
    NET_NUMBER_OF_DESKTOPS  = XInternAtom(display, "_NET_NUMBER_OF_DESKTOPS",  False);
    NET_WM_WINDOW_TYPE_DOCK = XInternAtom(display, "_NET_WM_WINDOW_TYPE_DOCK", False);
    NET_WM_WINDOW_TYPE      = XInternAtom(display, "_NET_WM_WINDOW_TYPE",      False);
    NET_WM_DESKTOP          = XInternAtom(display, "_NET_WM_DESKTOP",          False);
    NET_WM_STRUT            = XInternAtom(display, "_NET_WM_STRUT",            False);
    NET_WM_STRUT_PARTIAL    = XInternAtom(display, "_NET_WM_STRUT_PARTIAL",    False);
}


int X11Utils::getWindowProperty(Atom property, long len, long *buffer) {
    Atom type_ret;
    int format_ret, e;
    unsigned long items_ret;
    unsigned long after_ret;
    long *prop_data;

    e = XGetWindowProperty( QX11Info::display(), QX11Info::appRootWindow(),
                            property, 0, len, False, XA_CARDINAL, &type_ret, &format_ret,
                            &items_ret, &after_ret, (unsigned char **)&prop_data );

    if (e == Success) {
        for (int i =0; i < items_ret; ++i) {
            buffer[i] = prop_data[i];
        }
    }

    XFree(prop_data);
    return e;
}


QRect X11Utils::defineWorkarea() {
    const int RECT_SIZE = 4;
    long buffer[RECT_SIZE];
    QRect wa;
    if (getWindowProperty(NET_WORKAREA, RECT_SIZE, buffer) == Success) {
        wa = QRect(buffer[0],buffer[1],buffer[2],buffer[3]);
    }
    return wa;
}


unsigned int X11Utils::numberOfDesktops() {
    long *buffer;
    getWindowProperty(NET_NUMBER_OF_DESKTOPS, 1, buffer);
    int nitems = static_cast<int>(buffer[0]);
    unsigned int count = (nitems) ? nitems : 1;
    return count;
}


void X11Utils::defineDesktop(Window winid, int is_dock_window, unsigned int def_desktop) {
    Atom type;
    Atom property;
    unsigned char *data;

    if (is_dock_window) { //если нужно на всех рабочих столах, то делаем dock_window
        type     = XA_ATOM;
        property = NET_WM_WINDOW_TYPE;
        data     = (unsigned char *)&NET_WM_WINDOW_TYPE_DOCK;
    } else {
        type     = XA_CARDINAL;
        property = NET_WM_DESKTOP;
        data     = (unsigned char *)&def_desktop;
    }

    XChangeProperty(QX11Info::display(), winid, property, type,
                32, PropModeReplace, data, 1 );

}


void X11Utils::setStrut(Window winid, QRect app_rect, QString orient) {
    const int PARTIAL_STRUT_SIZE = 12;
    const int         STRUT_SIZE =  4;
    long int struts[PARTIAL_STRUT_SIZE] = { 0, };

    if (orient == "right") {
        struts[STRUT_RIGHT      ] = app_rect.width ();
        struts[STRUT_RIGHT_START] = app_rect.top   ();
        struts[STRUT_RIGHT_END  ] = app_rect.height();
    }

    else if (orient == "left") {
        struts[STRUT_LEFT       ] = app_rect.left() + app_rect.width();
        struts[STRUT_LEFT_END   ] = app_rect.left() + app_rect.width();
    }

    XChangeProperty(QX11Info::display(), winid, NET_WM_STRUT, XA_CARDINAL ,
                 32, PropModeReplace, (unsigned char *)&struts, STRUT_SIZE);

    XChangeProperty(QX11Info::display(), winid, NET_WM_STRUT_PARTIAL, XA_CARDINAL ,
                 32, PropModeReplace, (unsigned char *)&struts, PARTIAL_STRUT_SIZE);
}
