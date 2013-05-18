#ifndef KEYMAP_H
#define KEYMAP_H "$MirOS: X11/extras/evilwm/keymap.h,v 1.5 2006/10/16 20:43:19 tg Exp $"

#define KEY_NEXT	XK_Tab
#define KEY_NEW		XK_Return
#define KEY_TOPLEFT	XK_y
#define KEY_TOPRIGHT	XK_u
#define KEY_BOTTOMLEFT	XK_b
#define KEY_BOTTOMRIGHT	XK_n
#define KEY_LEFT	XK_h
#define KEY_RIGHT	XK_l
#define KEY_DOWN	XK_j
#define KEY_UP		XK_k
#define KEY_LOWER	XK_Insert
#define KEY_ALTLOWER	XK_KP_Insert
#define KEY_INFO	XK_i
#define KEY_MAXVERT	XK_equal
#define KEY_MAX		XK_x
#define KEY_FIX		XK_f
#define KEY_PREVDESK	XK_Left
#define KEY_NEXTDESK	XK_Right
/* Mixtures of Ctrl, Alt an Escape are used for things like VMWare and
 * XFree86/Cygwin, so the KILL key is an option in the Makefile  */
#ifndef KEY_KILL
#if 0
#define KEY_KILL	XK_Escape
#endif
#define KEY_KILL	XK_Pause
#endif
#define KEY_EXTERMF	XK_grave
#define KEY_ALTEXTERMF	XK_dead_grave
#define KEY_SLEFT	XK_q
#define KEY_SRIGHT	XK_r
#define KEY_SDOWN	XK_w
#define KEY_SUP		XK_e

#endif
