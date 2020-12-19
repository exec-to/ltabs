#include "x11utils.h"

QRect X11Utils::defineWorkarea() {
    return KWindowSystem::workArea();
}


unsigned int X11Utils::numberOfDesktops() {
    return KWindowSystem::numberOfDesktops();
}


void X11Utils::defineDesktop(Window winid, int is_dock_window, unsigned int def_desktop) {

    if (is_dock_window) {
        KWindowSystem::setType(winid, NET::Dock);
        KWindowSystem::setOnAllDesktops(winid, true);

    } else {
        KWindowSystem::setType(winid, NET::Dock);
        KWindowSystem::setOnAllDesktops(winid, false);
        KWindowSystem::setOnDesktop(winid, def_desktop+1);

    }
}


void X11Utils::setStrut(Window winid, QRect app_rect, QString orient) {

    if      (orient == "right") {
        KWindowSystem::setExtendedStrut	(winid, 0,0,0,
                                         app_rect.width(),
                                         app_rect.top(),
                                         app_rect.height(),
                                         0,0,0,0,0,0 );

    } else if (orient == "left" ) {
        KWindowSystem::setExtendedStrut	(winid, app_rect.width (),0,app_rect.width (),
                                         0,0,0,0,0,0,0,0,0 );
    }
}
