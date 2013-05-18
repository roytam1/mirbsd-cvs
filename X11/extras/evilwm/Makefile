# $MirOS: X11/extras/evilwm/Makefile,v 1.4 2006/08/14 18:57:57 tg Exp $

PROG=		evilwm
MAN=		evilwm.1
SRCS=		client.c events.c main.c misc.c new.c screen.c

LDADD+=		-L${X11LIBDIR} -lX11 -lXext
CPPFLAGS+=	-DVERSION=\"0.99.18\"
CPPFLAGS+=	-DSHAPE -DMOUSE -DSTDIO -DSOLIDDRAG -DCOLOURMAP -DVWM

# Enable a more informative and clear banner to be displayed on Ctrl+Alt+I.
CPPFLAGS+=	-DINFOBANNER
# Uncomment to show the same banner on moves and resizes.
# Note this can make things very SLOW!
#CPPFLAGS+=	-DINFOBANNER_MOVERESIZE

# Starting with evilwm 0.99.14, the "new move behaviour" is to only move a
# window if you move it by 5 or more pixels. This can be rather annoying,
# even if moving a window by accident. Uncomment the following line to
# revert to the older move behaviour.
CPPFLAGS+=	-DOLD_MOVE_BEHAVIOUR

# Use Motif hints to find if a window should be borderless.
# To use this option, you need to have the Motif development files installed.
.if exists(${X11BASE}/include/Xm/MwmUtil.h)
CPPFLAGS+=	-DMWM_HINTS
.endif

# Uncomment for snap-to-border support (thanks, Neil Drumm)
# Start evilwm with -snap num to enable (num is proximity in pixels to snap to)
CPPFLAGS+=	-DSNAP

# Uncomment the following line if you want to use Ctrl-Alt-Escape to kill
# windows (evilwm default) instead of Ctrl-Alt-Break (or just set it to
# what you want). This is useful under XFree86/Cygwin and VMware (probably)
#CPPFLAGS+=	-DKEY_KILL=XK_Escape

#CPPFLAGS+=	-DSANITY		# active sanity checks
#CPPFLAGS+=	-DDEBUG			# miscellaneous debugging
#CPPFLAGS+=	-DXDEBUG		# show some X calls

CFLAGS_misc.o+=	-Wno-cast-qual

.include <bsd.prog.mk>
