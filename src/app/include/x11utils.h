#pragma once

#include <QObject>
#include <QtCore>
#include <X11/Xutil.h>
#include <kwindowsystem.h>

class X11Utils
{
    private:
    //    X11Utils() {  }

    public:
        static QRect defineWorkarea();
        static void setStrut(Window winid, QRect app_rect, QString orient);
        static unsigned int numberOfDesktops();
        static void defineDesktop(Window winid, int all, unsigned int def_desktop);
};
