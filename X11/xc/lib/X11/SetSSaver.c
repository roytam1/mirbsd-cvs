/* $Xorg: SetSSaver.c,v 1.4 2001/02/09 02:03:36 xorgcvs Exp $ */
/*

Copyright 1986, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/
/* $XFree86: xc/lib/X11/SetSSaver.c,v 1.4 2001/12/14 19:54:06 dawes Exp $ */

#include "Xlibint.h"

int
XSetScreenSaver(dpy, timeout, interval, prefer_blank, allow_exp)
    register Display *dpy;
    int timeout, interval, prefer_blank, allow_exp;

{
    register xSetScreenSaverReq *req;

    LockDisplay(dpy);
    GetReq(SetScreenSaver, req);
    req->timeout = timeout;
    req->interval = interval;
    req->preferBlank = prefer_blank;
    req->allowExpose = allow_exp;
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}

