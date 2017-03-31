#include "desktoputils.h"

DesktopUtils::DesktopUtils() {   }

int DesktopUtils::freeAreaWidth = 0;
int DesktopUtils::freeAreaHeight = 0;

int DesktopUtils::getDesktopFreeAreaSize(Display* display, int screen, int *width, int *height)
{
  /* _NET_WORKAREA, x, y, width, height CARDINAL[][4]/32 */
  static Atom workarea = 0;
  Atom type;
  long *data;
  int format;
  unsigned long after, ndata;

  if (!workarea)
    workarea = XInternAtom(display, "_NET_WORKAREA", False);

  XGetWindowProperty(display, RootWindow(display, screen),
                     workarea, 0, LONG_MAX, False, XA_CARDINAL, &type, &format, &ndata,
                     &after, (unsigned char **)&data);
  if (type != XA_CARDINAL || data == NULL)
  {
    if (data) XFree(data);
    return 0;
  }

  *width = data[2];    /* get only for the first desktop */
  *height = data[3];

  XFree(data);
  return 1;
}

QRect DesktopUtils::initDesktopFreeAreaSize() {
    QRect r;
    getDesktopFreeAreaSize(QX11Info::display(),0, &freeAreaWidth, &freeAreaHeight);
    r.setWidth(freeAreaWidth);
    r.setHeight(freeAreaHeight);
    return r;
}
