/* $XFree86: xc/lib/X11/Cr.h,v 1.1 2003/04/13 19:22:14 dawes Exp $ */

#ifndef _CR_H_
#define _CR_H_

extern int _XUpdateGCCache(
    register GC gc,
    register unsigned long mask,
    register XGCValues *attr);
extern void _XNoticeCreateBitmap(
    Display         *dpy,
    Pixmap          pid,
    unsigned int    width,
    unsigned int    height);
extern void _XNoticePutBitmap(
    Display         *dpy,
    Drawable        draw,
    XImage          *image);
extern Cursor _XTryShapeBitmapCursor(
    Display         *dpy,
    Pixmap          source,
    Pixmap          mask,
    XColor          *foreground,
    XColor          *background,
    unsigned int    x,
    unsigned int    y);

#endif /* _CR_H_ */
