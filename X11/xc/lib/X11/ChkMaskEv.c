/* $Xorg: ChkMaskEv.c,v 1.4 2001/02/09 02:03:31 xorgcvs Exp $ */
/*

Copyright 1985, 1987, 1998  The Open Group

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
/* $XFree86: xc/lib/X11/ChkMaskEv.c,v 3.6 2001/12/14 19:53:58 dawes Exp $ */

#define NEED_EVENTS
#include "Xlibint.h"

extern long const _Xevent_to_mask[];

#define AllPointers (PointerMotionMask|PointerMotionHintMask|ButtonMotionMask)
#define AllButtons (Button1MotionMask|Button2MotionMask|Button3MotionMask|\
		    Button4MotionMask|Button5MotionMask)

/* 
 * Check existing events in queue to find if any match.  If so, return.
 * If not, flush buffer and see if any more events are readable. If one
 * matches, return.  If all else fails, tell the user no events found.
 */

Bool XCheckMaskEvent (dpy, mask, event)
        register Display *dpy;
	long mask;		/* Selected event mask. */
 	register XEvent *event;	/* XEvent to be filled in. */
{
	register _XQEvent *prev, *qelt;
	unsigned long qe_serial = 0;
	int n;			/* time through count */

        LockDisplay(dpy);
	prev = NULL;
	for (n = 3; --n >= 0;) {
	    for (qelt = prev ? prev->next : dpy->head;
		 qelt;
		 prev = qelt, qelt = qelt->next) {
		if ((qelt->event.type < LASTEvent) &&
		    (_Xevent_to_mask[qelt->event.type] & mask) &&
		    ((qelt->event.type != MotionNotify) ||
		     (mask & AllPointers) ||
		     (mask & AllButtons & qelt->event.xmotion.state))) {
		    *event = qelt->event;
		    _XDeq(dpy, prev, qelt);
		    UnlockDisplay(dpy);
		    return True;
		}
	    }
	    if (prev)
		qe_serial = prev->qserial_num;
	    switch (n) {
	      case 2:
		_XEventsQueued(dpy, QueuedAfterReading);
		break;
	      case 1:
		_XFlush(dpy);
		break;
	    }
	    if (prev && prev->qserial_num != qe_serial)
		/* another thread has snatched this event */
		prev = NULL;
	}
	UnlockDisplay(dpy);
	return False;
}
