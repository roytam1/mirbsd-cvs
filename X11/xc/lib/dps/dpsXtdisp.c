/*
 * dpsXtdisp.c
 *
 * (c) Copyright 1994 Adobe Systems Incorporated.
 * All rights reserved.
 * 
 * Permission to use, copy, modify, distribute, and sublicense this software
 * and its documentation for any purpose and without fee is hereby granted,
 * provided that the above copyright notices appear in all copies and that
 * both those copyright notices and this permission notice appear in
 * supporting documentation and that the name of Adobe Systems Incorporated
 * not be used in advertising or publicity pertaining to distribution of the
 * software without specific, written prior permission.  No trademark license
 * to use the Adobe trademarks is hereby granted.  If the Adobe trademark
 * "Display PostScript"(tm) is used to describe this software, its
 * functionality or for any other purpose, such use shall be limited to a
 * statement that this software works in conjunction with the Display
 * PostScript system.  Proper trademark attribution to reflect Adobe's
 * ownership of the trademark shall be given whenever any such reference to
 * the Display PostScript system is made.
 * 
 * ADOBE MAKES NO REPRESENTATIONS ABOUT THE SUITABILITY OF THE SOFTWARE FOR
 * ANY PURPOSE.  IT IS PROVIDED "AS IS" WITHOUT EXPRESS OR IMPLIED WARRANTY.
 * ADOBE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING ALL
 * IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NON- INFRINGEMENT OF THIRD PARTY RIGHTS.  IN NO EVENT SHALL ADOBE BE LIABLE
 * TO YOU OR ANY OTHER PARTY FOR ANY SPECIAL, INDIRECT, OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER WHETHER IN AN ACTION OF CONTRACT,
 * NEGLIGENCE, STRICT LIABILITY OR ANY OTHER ACTION ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.  ADOBE WILL NOT
 * PROVIDE ANY TRAINING OR OTHER SUPPORT FOR THE SOFTWARE.
 * 
 * Adobe, PostScript, and Display PostScript are trademarks of Adobe Systems
 * Incorporated which may be registered in certain jurisdictions
 * 
 * Author:  Adobe Systems Incorporated
 */

#include <X11/Intrinsic.h>

#if XtSpecificationRelease < 6

#include "dpsassert.h"

void XDPSSetXtEventDispatching(Display *dpy)
{
    DPSFatalProc(NULL, "Attempt to use XDPSSetXtEventDispatching with pre-R6 Intrinsics\n");
    exit(1);
}

#else

#include <DPS/XDPSlib.h>
#include <DPS/dpsXclient.h>

typedef struct _DpyProcRec {
    Display *dpy;
    XtEventDispatchProc oldproc;
    struct _DpyProcRec *next;
} DpyProcRec;

static DpyProcRec *dpyProcList = NULL;

static Boolean NXDispatcher(XEvent *event)
{
    DpyProcRec *d;

    if (XDPSDispatchEvent(event)) return True;

    for (d = dpyProcList; d != NULL && d->dpy != event->xany.display;
	 d = d->next) {}
    if (d != NULL) return (*(d->oldproc))(event);
    else return False;
}
	
void XDPSSetXtEventDispatching(Display *dpy)
{
    int codes;
    XExtCodes *c;

    codes = XDPSLInit(dpy, (int *) NULL, (char **) NULL);

    if (codes == -1) return; 	/* No extension or NX, so nothing to do */
    else {
	(void) XDPSSetEventDelivery(dpy, dps_event_pass_through);
	c = XDPSLGetCodes(dpy);

	/* First check for NX */
	if (!c->first_event) {
	    DpyProcRec *d = XtNew(DpyProcRec);
	    d->dpy = dpy;
	    d->next = dpyProcList;
	    d->oldproc =
		    XtSetEventDispatcher(dpy, ClientMessage, NXDispatcher);
	    dpyProcList = d;

	} else {
	    /* Extension */
	    (void) XtSetEventDispatcher(dpy, c->first_event + PSEVENTSTATUS,
				(XtEventDispatchProc) XDPSDispatchEvent);
	    (void) XtSetEventDispatcher(dpy, c->first_event + PSEVENTOUTPUT,
				(XtEventDispatchProc) XDPSDispatchEvent);
	    (void) XtSetEventDispatcher(dpy, c->first_event + PSEVENTREADY,
				(XtEventDispatchProc) XDPSDispatchEvent);
	}
    }
}

#endif
