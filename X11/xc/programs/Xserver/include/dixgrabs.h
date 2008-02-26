/* $XFree86: xc/programs/Xserver/include/dixgrabs.h,v 3.1 2003/04/27 21:31:04 herrb Exp $ */
/************************************************************

Copyright 1996 by Thomas E. Dickey <dickey@clark.net>

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its
documentation for any purpose and without fee is hereby granted,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation, and that the name of the above listed
copyright holder(s) not be used in advertising or publicity pertaining
to distribution of the software without specific, written prior
permission.

THE ABOVE LISTED COPYRIGHT HOLDER(S) DISCLAIM ALL WARRANTIES WITH REGARD
TO THIS SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
AND FITNESS, IN NO EVENT SHALL THE ABOVE LISTED COPYRIGHT HOLDER(S) BE
LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

#ifndef DIXGRABS_H
#define DIXGRABS_H 1

extern GrabPtr CreateGrab(
	int /* client */,
	DeviceIntPtr /* device */,
	WindowPtr /* window */,
	Mask /* eventMask */,
	Bool /* ownerEvents */,
	Bool /* keyboardMode */,
	Bool /* pointerMode */,
	DeviceIntPtr /* modDevice */,
	unsigned short /* modifiers */,
	int /* type */,
	KeyCode /* keybut */,
	WindowPtr /* confineTo */,
	CursorPtr /* cursor */);

extern int DeletePassiveGrab(
	pointer /* value */,
	XID /* id */);

extern Bool GrabMatchesSecond(
	GrabPtr /* pFirstGrab */,
	GrabPtr /* pSecondGrab */);

extern int AddPassiveGrabToList(
	GrabPtr /* pGrab */);

extern Bool DeletePassiveGrabFromList(
	GrabPtr /* pMinuendGrab */);

#endif /* DIXGRABS_H */
