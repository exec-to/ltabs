#pragma once

#include <QObject>
#include <QtX11Extras/QtX11Extras>
#include <QtX11Extras/QX11Info>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/Xutil.h>

class DesktopUtils
{

private:
    DesktopUtils();
    static int getDesktopFreeAreaSize(Display* display, int screen, int *width, int *height);
    static int freeAreaWidth;
    static int freeAreaHeight;


public:
    static QRect initDesktopFreeAreaSize();


};
