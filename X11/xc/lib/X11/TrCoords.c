/* $Xorg: TrCoords.c,v 1.4 2001/02/09 02:03:37 xorgcvs Exp $ */
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

#define NEED_REPLIES
#include "Xlibint.h"

Bool XTranslateCoordinates(dpy, src_win, dest_win, src_x, src_y, 
		      dst_x, dst_y, child)
     register Display *dpy;
     Window src_win, dest_win;
     int src_x, src_y;
     int *dst_x, *dst_y;
     Window *child;
{       
    register xTranslateCoordsReq *req;
    xTranslateCoordsReply rep;

    LockDisplay(dpy);
    GetReq(TranslateCoords, req);
    req->srcWid = src_win;
    req->dstWid = dest_win;
    req->srcX = src_x;
    req->srcY = src_y;
    if (_XReply (dpy, (xReply *)&rep, 0, xTrue) == 0) {
	    UnlockDisplay(dpy);
	    SyncHandle();
	    return(False);
	}
	
    *child = rep.child;
    *dst_x = cvtINT16toInt (rep.dstX);
    *dst_y = cvtINT16toInt (rep.dstY);
    UnlockDisplay(dpy);
    SyncHandle();
    return ((int)rep.sameScreen);
}

