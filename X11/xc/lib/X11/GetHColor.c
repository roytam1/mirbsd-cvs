/* $Xorg: GetHColor.c,v 1.4 2001/02/09 02:03:33 xorgcvs Exp $ */
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

Status XAllocColor(dpy, cmap, def)
register Display *dpy;
Colormap cmap;
XColor *def;
{
    Status status;
    xAllocColorReply rep;
    register xAllocColorReq *req;
    LockDisplay(dpy);
    GetReq(AllocColor, req);

    req->cmap = cmap;
    req->red = def->red;
    req->green = def->green;
    req->blue = def->blue;

    status = _XReply(dpy, (xReply *) &rep, 0, xTrue);
    if (status) {
      def->pixel = rep.pixel;
      def->red = rep.red;
      def->green = rep.green;
      def->blue = rep.blue;
      }
    UnlockDisplay(dpy);
    SyncHandle();
    return(status);
}
