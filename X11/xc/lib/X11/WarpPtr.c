/* $Xorg: WarpPtr.c,v 1.4 2001/02/09 02:03:37 xorgcvs Exp $ */
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
/* $XFree86: xc/lib/X11/WarpPtr.c,v 1.4 2001/12/14 19:54:08 dawes Exp $ */

#include "Xlibint.h"

int
XWarpPointer(dpy, src_win, dest_win, src_x, src_y, src_width, src_height,
	     dest_x, dest_y)
     register Display *dpy;
     Window src_win, dest_win;
     int src_x, src_y;
     unsigned int src_width, src_height;
     int dest_x, dest_y;
{       
    register xWarpPointerReq *req;

    LockDisplay(dpy);
    GetReq(WarpPointer, req);
    req->srcWid = src_win;
    req->dstWid = dest_win;
    req->srcX = src_x;
    req->srcY = src_y;
    req->srcWidth = src_width;
    req->srcHeight = src_height;
    req->dstX = dest_x;
    req->dstY = dest_y;
    UnlockDisplay(dpy);
    SyncHandle();
    return 1;
}

