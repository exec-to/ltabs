#include "x11utils.h"

Atom X11Utils::NET_WORKAREA            = 0;
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
    NET_WM_STRUT_PARTIAL    = XInternAtom(display, "_NET_WM_STRUT_PARTIAL",    False);
}


/*void* X11Utils::property(int &nitems)
{
    Atom type_ret;
    int format_ret;
    unsigned long items_ret;
    unsigned long after_ret;
    long *prop_data;

    // на основании атома и его типа берём значение свойства
    if( XGetWindowProperty(
                QX11Info::display(),
                QX11Info::appRootWindow(),
                NET_NUMBER_OF_DESKTOPS,
                0,
                LONG_MAX,
                False,
                XA_CARDINAL,
                &type_ret,
                &format_ret,
                &items_ret,
                &after_ret,
                (unsigned char **)&prop_data) != Success )
        return 0;

    // количество полученных элементов
    nitems = *((int*)prop_data);
    qDebug() << nitems;
    return prop_data;
}*/


int X11Utils::getWindowProperty(Atom property, long &buffer) {
    Atom type_ret;
    int format_ret;
    unsigned long items_ret;
    unsigned long after_ret;
    long *prop_data;

    if( XGetWindowProperty(
                QX11Info::display(),
                QX11Info::appRootWindow(),
                property,
                0,
                LONG_MAX,
                False,
                XA_CARDINAL,
                &type_ret,
                &format_ret,
                &items_ret,
                &after_ret,
                (unsigned char **)&prop_data) != Success )
        return 0;

    buffer = *prop_data;
    XFree(prop_data);
    return 0;
}


QRect X11Utils::availableGeometry() {
   /* Atom type_ret;
    int format_ret;
    long *prop_data;
    unsigned long after_ret;
    unsigned long items_ret;

    qDebug() << *prop_data;

    qDebug() << prop_data[0];
    qDebug() << prop_data[1];
    qDebug() << prop_data[2];
    qDebug() << prop_data[3];

    XGetWindowProperty(
                QX11Info::display(),
                QX11Info::appRootWindow(),
                NET_WORKAREA,
                0,
                LONG_MAX,
                False,
                XA_CARDINAL,
                &type_ret,
                &format_ret,
                &items_ret,
                &after_ret,
                (unsigned char **)&prop_data);

    if (type_ret != XA_CARDINAL || prop_data == NULL)
    {
      if (prop_data) XFree(prop_data);
      return QRect(0,0,0,0);
    }
    qDebug() << *prop_data;
    qDebug() << (unsigned char **)&prop_data;

    qDebug() << prop_data[0];
    qDebug() << prop_data[1];
    qDebug() << prop_data[2];
    qDebug() << prop_data[3];*/
    long buffer;
    getWindowProperty(NET_WORKAREA, buffer);

    //QRect wa(prop_data[0],prop_data[1],prop_data[2],prop_data[3]);
    QRect wa(buffer,buffer,buffer,buffer);
    //XFree(prop_data);
    return wa;
}


unsigned int X11Utils::desktopCount() {
    long buffer;
    getWindowProperty(NET_NUMBER_OF_DESKTOPS, buffer);
    int nitems = static_cast<int>(buffer);
    unsigned int count = (nitems) ? nitems : 1;
    return count;
}


void X11Utils::setOnDesktops(Window winid, int all, unsigned int d) {
    Display *display  = QX11Info::display();
    if (all) { //если нужно на всех рабочих столах, то делаем док


        XChangeProperty
        (
            display,
            winid,
            NET_WM_WINDOW_TYPE,
            XA_ATOM ,
            32,
            PropModeReplace,
            (unsigned char *)&NET_WM_WINDOW_TYPE_DOCK, 1
        );

    } else {
        XChangeProperty
        (
            display,
            winid,
            NET_WM_DESKTOP,
            XA_CARDINAL,
            32,
            PropModeReplace,
            (unsigned char *)&d, 1
        );
    }
}


void X11Utils::setStrut(Window winid, int height, int width, unsigned int start_x, unsigned int start_y, QString dockEdge) {

    Display *display  = QX11Info::display();
    int right_start_y = start_y;
    int right_end_y = height;
    int right = width;
    int left = start_x + width;
    long int insets[12] = {0, right, 0, 0, 0, 0, right_start_y, right_end_y, 0, 0, 0, 0};

    if (dockEdge != "right") {
        insets[0] = left;
        insets[1] = 0;
        insets[5] = left;
        insets[6] = 0;
        insets[7] = 0;
    }

    XChangeProperty(display,
                  winid,
                 NET_WM_STRUT_PARTIAL,
                 XA_CARDINAL ,
                 32,
                 PropModeReplace,
                 (unsigned char *)&insets, 12);
}
