/* evilwm - Minimalist Window Manager for X
 * Copyright (C) 1999-2002 Ciaran Anscomb <evilwm@6809.org.uk>
 * see README for license and other details. */

#include "evilwm.h"
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <X11/cursorfont.h>
#include <stdio.h>
#ifdef SHAPE
#include <X11/extensions/shape.h>
#endif

Display		*dpy;
int 		num_screens;
ScreenInfo	*screens;
ScreenInfo	*current_screen;
Client		*current = NULL;
Window		initialising = None;
XFontStruct	*font;
Client		*head_client;
Atom		xa_wm_state;
Atom		xa_wm_change_state;
Atom		xa_wm_protos;
Atom		xa_wm_delete;
Atom		xa_wm_cmapwins;
Cursor		move_curs;
Cursor		resize_curs;
const char	*opt_display = "";
const char	*opt_font = DEF_FONT;
const char	*opt_fg = DEF_FG;
const char	*opt_bg = DEF_BG;
const char	**opt_term = NULL;
int		opt_bw = DEF_BW;
#ifdef VWM
const char	*opt_fc = DEF_FC;
int		vdesk = KEY_TO_VDESK(XK_1);
#endif
#ifdef SNAP
int		opt_snap = 0;
#endif
#ifdef SHAPE
int		have_shape, shape_event;
#endif
int		quitting = 0;
#ifdef MWM_HINTS
Atom		mwm_hints;
#endif
unsigned int numlockmask = 0;

static void *xmalloc(size_t size);

static void *xmalloc(size_t size) {
	void *ptr = malloc(size);
	if (!ptr) {
#ifdef STDIO
		fprintf(stderr,"out of memory, looking for %d bytes\n",size);
#endif
		exit(1);
	}
	return ptr;
}

int main(int argc, char *argv[]) {
	struct sigaction act;
	int i;
	XEvent ev;

	for (i = 1; i < argc; i++) {
		if (!strcmp(argv[i], "-fn") && i+1<argc)
			opt_font = argv[++i];
		else if (!strcmp(argv[i], "-display") && i+1<argc) {
			opt_display = argv[++i];
		}
		else if (!strcmp(argv[i], "-fg") && i+1<argc)
			opt_fg = argv[++i];
		else if (!strcmp(argv[i], "-bg") && i+1<argc)
			opt_bg = argv[++i];
#ifdef VWM
		else if (!strcmp(argv[i], "-fc") && i+1<argc)
			opt_fc = argv[++i];
#endif
		else if (!strcmp(argv[i], "-bw") && i+1<argc)
			opt_bw = atoi(argv[++i]);
		else if (!strcmp(argv[i], "-term") && i+1<argc) {
			opt_term = (const char **)xmalloc(3 * sizeof(const char *));
			opt_term[0] = argv[++i];
			opt_term[1] = opt_term[0];
			opt_term[2] = NULL;
		} else if (!strcmp(argv[i], "-snap") && i+1<argc) {
			opt_snap = atoi(argv[++i]);
#ifdef STDIO
		} else if (!strcmp(argv[i], "-V")) {
			printf("evilwm version " VERSION " $MirOS$\n");
			exit(0);
#endif
		} else {
#ifdef STDIO
			printf("usage: evilwm [-display display] [-term termprog] [-fg foreground]\n");
			printf("\t[-bg background] [-bw borderwidth] [-snap num] [-V]\n");
#endif
			exit(2);
		}
	}
	if (!opt_term) {
		opt_term = (const char **)xmalloc(3 * sizeof(const char *));
		opt_term[0] = DEF_TERM;
		opt_term[1] = opt_term[0];
		opt_term[2] = NULL;
	}

	act.sa_handler = handle_signal;
	sigemptyset(&act.sa_mask);
	act.sa_flags = 0;
	sigaction(SIGTERM, &act, NULL);
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGHUP, &act, NULL);

	setup_display();

#ifdef SHAPE
	have_shape = XShapeQueryExtension(dpy, &shape_event, &i);
#endif

	/* main event loop here */
	for (;;) {
		XNextEvent(dpy, &ev);
		switch (ev.type) {
			case KeyPress:
				handle_key_event(&ev.xkey); break;
#ifdef MOUSE
			case ButtonPress:
				handle_button_event(&ev.xbutton); break;
#endif
			case ConfigureRequest:
				handle_configure_request(&ev.xconfigurerequest); break;
			case MapRequest:
				handle_map_request(&ev.xmaprequest); break;
#ifdef VDESK
			case ClientMessage:
				handle_client_message(&ev.xclient); break;
#endif
#ifdef COLOURMAP
			case ColormapNotify:
				handle_colormap_change(&ev.xcolormap); break;
#endif
			case EnterNotify:
				handle_enter_event(&ev.xcrossing); break;
			case LeaveNotify:
				handle_leave_event(&ev.xcrossing); break;
			case PropertyNotify:
				handle_property_change(&ev.xproperty); break;
			case UnmapNotify:
				handle_unmap_event(&ev.xunmap); break;
			default:
#ifdef SHAPE
				if (have_shape && ev.type == shape_event) {
					handle_shape_event((XShapeEvent *)&ev);
				}
#endif
		}
	}
	return 1;
}

void setup_display() {
	XGCValues gv;
	XSetWindowAttributes attr;
	XColor dummy;
	XModifierKeymap *modmap;
	KeySym *keysym;
	KeySym keys_to_grab[] = {
		KEY_NEW, KEY_KILL,
		KEY_TOPLEFT, KEY_TOPRIGHT, KEY_BOTTOMLEFT, KEY_BOTTOMRIGHT,
		KEY_LEFT, KEY_RIGHT, KEY_DOWN, KEY_UP,
		KEY_SLEFT, KEY_SRIGHT, KEY_SDOWN, KEY_SUP,
		KEY_LOWER, KEY_ALTLOWER, KEY_INFO, KEY_MAXVERT, KEY_MAX,
#ifdef VWM
		KEY_FIX, KEY_PREVDESK, KEY_NEXTDESK,
		XK_1, XK_2, XK_3, XK_4, XK_5, XK_6, XK_7, XK_8,
#endif
		KEY_EXITF, KEY_ALTEXITF,
		0
	};
	/* used in scanning windows (XQueryTree) */
	unsigned int i, j, nwins;
	Window dw1, dw2, *wins;
	XWindowAttributes winattr;

	dpy = XOpenDisplay(opt_display);
	if (!dpy) { 
#ifdef STDIO
		fprintf(stderr, "can't open display %s\n", opt_display);
#endif
		exit(1);
	}
	XSetErrorHandler(handle_xerror);

	xa_wm_state = XInternAtom(dpy, "WM_STATE", False);
	xa_wm_change_state = XInternAtom(dpy, "WM_CHANGE_STATE", False);
	xa_wm_protos = XInternAtom(dpy, "WM_PROTOCOLS", False);
	xa_wm_delete = XInternAtom(dpy, "WM_DELETE_WINDOW", False);
#ifdef COLOURMAP
	xa_wm_cmapwins = XInternAtom(dpy, "WM_COLORMAP_WINDOWS", False);
#endif
#ifdef MWM_HINTS
	mwm_hints = XInternAtom(dpy, _XA_MWM_HINTS, False);
#endif

	font = XLoadQueryFont(dpy, opt_font);
	if (!font) font = XLoadQueryFont(dpy, DEF_FONT);

	move_curs = XCreateFontCursor(dpy, XC_fleur);
	resize_curs = XCreateFontCursor(dpy, XC_plus);

	/* find out which modifier is NumLock - we'll use this when grabbing
	 * every combination of modifiers we can think of */
	modmap = XGetModifierMapping(dpy);
	for (i = 0; i < 8; i++) {
		for (j = 0; j < modmap->max_keypermod; j++) {
			if (modmap->modifiermap[i*modmap->max_keypermod+j] == XKeysymToKeycode(dpy, XK_Num_Lock)) {
				numlockmask = (1<<i);
#ifdef DEBUG
				fprintf(stderr, "setup_display() : XK_Num_Lock is (1<<0x%02x)\n", i);
#endif
			}
		}
	}
	XFreeModifiermap(modmap);

	/* set up GC parameters - same for each screen */
	gv.function = GXinvert;
	gv.subwindow_mode = IncludeInferiors;
	gv.line_width = 1;  /* opt_bw */
	gv.font = font->fid;

	/* set up root window attributes - same for each screen */
	attr.event_mask = ChildMask | PropertyChangeMask | EnterWindowMask | LeaveWindowMask
#ifdef COLOURMAP
		| ColormapChangeMask
#endif
#ifdef MOUSE
		| ButtonMask
#endif
		;

	/* now set up each screen in turn */
	num_screens = ScreenCount(dpy);
	screens = (ScreenInfo *)xmalloc(num_screens * sizeof(ScreenInfo));
	for (i = 0; i < num_screens; i++) {
		char *ds, *colon, *dot;
		ds = DisplayString(dpy);
		/* set up DISPLAY environment variable to use */
		colon = rindex(ds, ':');
		if (colon && num_screens > 1) {
			int xlen = 14 + strlen(ds);

			screens[i].display = (char *)xmalloc(xlen);
			strlcpy(screens[i].display, "DISPLAY=", xlen);
			strlcat(screens[i].display, ds, xlen);
			colon = rindex(screens[i].display, ':');
			dot = index(colon, '.');
			if (!dot)
				dot = colon + strlen(colon);
			snprintf(dot, 5, ".%d", i);
		} else
			screens[i].display = NULL;

		screens[i].screen = i;
		screens[i].root = RootWindow(dpy, i);

		XAllocNamedColor(dpy, DefaultColormap(dpy, i), opt_fg, &screens[i].fg, &dummy);
		XAllocNamedColor(dpy, DefaultColormap(dpy, i), opt_bg, &screens[i].bg, &dummy);
#ifdef VWM
		XAllocNamedColor(dpy, DefaultColormap(dpy, i), opt_fc, &screens[i].fc, &dummy);
#endif

		screens[i].invert_gc = XCreateGC(dpy, screens[i].root, GCFunction | GCSubwindowMode | GCLineWidth | GCFont, &gv);

		XChangeWindowAttributes(dpy, screens[i].root, CWEventMask, &attr);
		/* Unfortunately grabbing AnyKey under Solaris seems not to work */
		/* XGrabKey(dpy, AnyKey, ControlMask|Mod1Mask, root, True, GrabModeAsync, GrabModeAsync); */
		/* So now I grab each and every one. */

		for (keysym = keys_to_grab; *keysym; keysym++) {
			grab_keysym(screens[i].root, ControlMask|Mod1Mask, *keysym);
		}
		grab_keysym(screens[i].root, Mod1Mask, XK_Tab);

		/* scan all the windows on this screen */
#ifdef XDEBUG
		fprintf(stderr, "main:XQueryTree(); ");
#endif
		XQueryTree(dpy, screens[i].root, &dw1, &dw2, &wins, &nwins);
#ifdef XDEBUG
		fprintf(stderr, "%d windows\n", nwins);
#endif
		for (j = 0; j < nwins; j++) {
			XGetWindowAttributes(dpy, wins[j], &winattr);
			if (!winattr.override_redirect && winattr.map_state == IsViewable)
				make_new_client(wins[j], &screens[i]);
		}
		XFree(wins);
	}
	current_screen = find_screen(DefaultScreen(dpy));
}
