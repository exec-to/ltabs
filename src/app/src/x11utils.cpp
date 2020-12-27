#include "x11utils.h"

QRect X11Utils::workarea() {
    return KWindowSystem::workArea();
}


unsigned int X11Utils::numberOfDesktops() {
    return KWindowSystem::numberOfDesktops();
}


void X11Utils::setOnDesktop(Window winid, unsigned int virtual_desktop) {

    bool all_desktops = (virtual_desktop == 0);

    KWindowSystem::setType(winid, NET::Dock);
    KWindowSystem::setOnAllDesktops(winid, all_desktops);

    if (!all_desktops) {
        KWindowSystem::setOnDesktop(winid, virtual_desktop);
    }
}


void X11Utils::setStrut(Window winid, QRect app_rect, QString orient) {

    if      (orient == "right") {
        KWindowSystem::setExtendedStrut	(winid, 0,0,0,
                                         app_rect.width(), app_rect.top(), app_rect.height(),
                                         0,0,0,0,0,0 );

    } else if (orient == "left" ) {
        KWindowSystem::setExtendedStrut	(winid, app_rect.width (),0,app_rect.width (),
                                         0,0,0,0,0,0,0,0,0 );
    }
}
