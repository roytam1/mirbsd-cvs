/* $OpenBSD: callbacks.h,v 1.5 2002/12/31 16:31:30 matthieu Exp $ */
/*
 * Copyright (c) 2002 Matthieu Herrb
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 *    - Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *    - Redistributions in binary form must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the documentation and/or other materials provided
 *      with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

extern XtInputId inputId;

extern void getInput(XtPointer, int *, XtInputId *);
extern void on_filter_select(Widget, XtPointer, XtPointer);
extern void on_error_select(Widget, XtPointer, XtPointer);
extern void on_error_entry_changed(Widget, XEvent *, String *, Cardinal *);
extern void on_denyone_clicked(Widget, XtPointer, XtPointer);
extern void on_permitonce_clicked(Widget, XtPointer, XtPointer);
extern void on_deny_clicked(Widget, XtPointer, XtPointer);
extern void on_permit_clicked(Widget, XtPointer, XtPointer);
extern void on_filter_entry_changed(Widget, XEvent *, String *, Cardinal *);
extern void on_detachbutton_clicked(Widget, XtPointer, XtPointer);
extern void on_reviewbutton_clicked(Widget, XtPointer, XtPointer);
extern void on_wizard_clicked(Widget, XtPointer, XtPointer);
extern void on_wizard_ok_clicked(Widget, XtPointer, XtPointer);
extern void on_wizard_cancel_clicked(Widget, XtPointer, XtPointer);
extern void on_killbutton_clicked(Widget, XtPointer, XtPointer);
extern void on_done_button(Widget, XtPointer, XtPointer);



