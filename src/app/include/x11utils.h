#pragma once

#include <QObject>
#include <QtCore>
#include <X11/Xutil.h>
#include <kwindowsystem.h>

class X11Utils
{
    public:
        static QRect workarea();
        static void setStrut(Window winid, QRect app_rect, QString orient);
        static unsigned int numberOfDesktops();
        static void setOnDesktop(Window winid, unsigned int def_desktop);
};
