/* evilwm - Minimalist Window Manager for X
 * Copyright (C) 1999-2002 Ciaran Anscomb <evilwm@6809.org.uk>
 * see README for license and other details. */

#include "evilwm.h"
#include <stdlib.h>
#include <stdio.h>
#ifdef SHAPE
#include <X11/extensions/shape.h>
#endif

static int send_xmessage(Window w, Atom a, long x);

/* used all over the place.  return the client that has specified window as
 * either window or parent */

Client *find_client(Window w) {
	Client *c;

	for (c = head_client; c; c = c->next)
		if (w == c->parent || w == c->window)
			return c;
	return NULL;
}

static void __set_wm_state(const Window win, const Atom a, int state, long vis) {
	long data[2];

	data[0] = (long) state;
	data[1] = vis;

	XChangeProperty(dpy, win, a, a,
		32, PropModeReplace, (unsigned char *)data, 2);
}
void set_wm_state(Client *c, int state) {
	/* iconify window and set state */
	__set_wm_state(c->window, xa_wm_state, state, None);
}

static long * _g_wm_state(const Window win, const Atom where) {
	Atom real_type;
	int real_format;
	unsigned long n, extra;
	unsigned char *data;

	if ((XGetWindowProperty(dpy, win, where, 0L, 2L, False,
			AnyPropertyType, &real_type, &real_format, &n,
			&extra, &data) == Success) && n) {
		return (long *)data;
	}
	return NULL;
}
static int __wm_state(const Window win, const Atom where) {
	long *data, state = WithdrawnState;

	data = _g_wm_state(win, where);
	if (data) {
		state = *data;
		XFree(data);
	}
	return state;
}
int wm_state(Client *c) { return __wm_state(c->window, xa_wm_state); }

void send_config(Client *c) {
	XConfigureEvent ce;

	ce.type = ConfigureNotify;
	ce.event = c->window;
	ce.window = c->window;
	ce.x = c->x;
	ce.y = c->y;
	ce.width = c->width;
	ce.height = c->height;
	ce.border_width = 0;
	ce.above = None;
	ce.override_redirect = 0;

	XSendEvent(dpy, c->window, False, StructureNotifyMask, (XEvent *)&ce);
}

void remove_client(Client *c) {
	Client *p;

#ifdef DEBUG
	fprintf(stderr, "remove_client() : Removing...\n");
#endif

	XGrabServer(dpy);
	XSetErrorHandler(ignore_xerror);

	if (!quitting) {
#ifdef DEBUG
		fprintf(stderr, "\tremove_client() : setting WithdrawnState\n");
#endif
		set_wm_state(c, WithdrawnState);
		XRemoveFromSaveSet(dpy, c->window);
	}

	ungravitate(c);
	XSetWindowBorderWidth(dpy, c->window, 1);
	XReparentWindow(dpy, c->window, c->screen->root, c->x, c->y);
	if (c->parent)
		XDestroyWindow(dpy, c->parent);

	if (head_client == c) head_client = c->next;
	else for (p = head_client; p && p->next; p = p->next)
		if (p->next == c) p->next = c->next;

	if (c->size) XFree(c->size);
	if (current == c)
		current = NULL;  /* an enter event should set this up again */
	free(c);
#ifdef DEBUG
	{
		Client *p;
		int i = 0;
		for (p = head_client; p; p = p->next)
			i++;
		fprintf(stderr, "\tremove_client() : free(), window count now %d\n", i);
	}
#endif

	XSync(dpy, False);
	XSetErrorHandler(handle_xerror);
	XUngrabServer(dpy);
}

void change_gravity(Client *c, int multiplier) {
	int dx = 0, dy = 0;
	int gravity = (c->size->flags & PWinGravity) ?
		c->size->win_gravity : NorthWestGravity;

	switch (gravity) {
		case NorthWestGravity:
		case SouthWestGravity:
		case NorthEastGravity:
		case StaticGravity:
			dx = c->border;
		case NorthGravity:
			dy = c->border; break;
	}

	c->x += multiplier * dx;
	c->y += multiplier * dy;
#ifdef DEBUG
	if (dx || dy) {
		fprintf(stderr, "change_gravity() : window adjustment of %d,%d for ", multiplier * dx, multiplier * dy);
	switch (gravity) {
		case NorthWestGravity: fprintf(stderr, "NorthWestGravity\n"); break;
		case SouthWestGravity: fprintf(stderr, "SouthWestGravity\n"); break;
		case NorthEastGravity: fprintf(stderr, "NorthEastGravity\n"); break;
		case NorthGravity: fprintf(stderr, "NorthGravity\n"); break;
		case StaticGravity: fprintf(stderr, "StaticGravity\n"); break;
		default: fprintf(stderr, "unhandled gravity %d\n", gravity); break;
	}
	}
#endif
}

void send_wm_delete(Client *c) {
	int i, n, found = 0;
	Atom *protocols;

	if (c) {
		if (XGetWMProtocols(dpy, c->window, &protocols, &n)) {
			for (i=0; i<n; i++) if (protocols[i] == xa_wm_delete) found++;
			XFree(protocols);
		}
		if (found) send_xmessage(c->window, xa_wm_protos, xa_wm_delete);
		else XKillClient(dpy, c->window);
	}
}

static int send_xmessage(Window w, Atom a, long x) {
	XEvent ev;

	ev.type = ClientMessage;
	ev.xclient.window = w;
	ev.xclient.message_type = a;
	ev.xclient.format = 32;
	ev.xclient.data.l[0] = x;
	ev.xclient.data.l[1] = CurrentTime;

	return XSendEvent(dpy, w, False, NoEventMask, &ev);
}
/*
void client_to_front(Client *c) {
	Client *p;

	if (head_client == c) {
		head_client = c->next;
	}
	for (p = head_client; p->next; p = p->next) {
		if (p->next == c) {
			p->next = c->next;
		}
	}
	p->next = c;
	c->next = NULL;
}
*/

#ifdef SHAPE
void set_shape(Client *c) {
	int n, order;
	XRectangle *rect;

	rect = XShapeGetRectangles(dpy, c->window, ShapeBounding, &n, &order);
	if (n > 1)
		XShapeCombineShape(dpy, c->parent, ShapeBounding, c->border,
				c->border, c->window, ShapeBounding, ShapeSet);
	XFree((void*)rect);
}
#endif

void client_update_current(Client *c, Client *newcurrent) {
	if (c) {
#ifdef VWM
		if (c->vdesk == STICKY)
			XSetWindowBackground(dpy, c->parent, c == newcurrent ? c->screen->fc.pixel : c->screen->bg.pixel);
		else
#endif
			XSetWindowBackground(dpy, c->parent, c == newcurrent ? c->screen->fg.pixel : c->screen->bg.pixel);
		XClearWindow(dpy, c->parent);
	}
	current = newcurrent;
}
