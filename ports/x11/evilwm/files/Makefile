# $MirOS$

PROG=	evilwm
MAN=	evilwm.1
SRCS=	allinone.c

.if defined(DESTDIR) && !empty(DESTDIR) && defined(TRUEPREFIX)
PREFIX:=	${TRUEPREFIX}
.endif
BINDIR=		${PREFIX}/bin
MANDIR=		${PREFIX}/man/cat

LDADD+=		-L$(X11LIBDIR) -lX11 -lXext
CPPFLAGS+=	-DSHAPE -DVERSION=\"${EVILVERSION}\"
CLEANFILES+=	allinone.c

# See the file INSTALL for descriptions of these
#
CPPFLAGS+=	-DMOUSE
CPPFLAGS+=	-DSTDIO
CPPFLAGS+=	-DSOLIDDRAG
CPPFLAGS+=	-DCOLOURMAP

# To support virtual desktops, uncomment exactly one of the following lines:
CPPFLAGS+=	-DVWM
#CPPFLAGS+=	-DVDESK

# Enable a more informative and clear banner to be displayed on Ctrl+Alt+I.
CPPFLAGS+=	-DINFOBANNER
# Uncomment to show the same banner on moves and resizes.  Note this can
# make things very SLOW!
#CPPFLAGS+=	-DINFOBANNER_MOVERESIZE

# Starting with evilwm 0.99.14, the "new move behaviour" is to only move a
# window if you move it by 5 or more pixels. In my experience, if you move
# a window by accident, it doesn't help - but rather annoy. -mirabile
# Uncomment the line below to revert this.
#CPPFLAGS+=	-DOLD_MOVE_BEHAVIOUR

# Use Motif hints to find if a window should be borderless.
# To use this option, you need to have the Motif development files installed.
.if exists(${X11BASE}/include/Xm/MwmUtil.h)
CPPFLAGS+=	-DMWM_HINTS
.endif

# Uncomment for snap-to-border support (thanks, Neil Drumm)
# Start evilwm with -snap num to enable (num is proximity in pixels to snap to)
CPPFLAGS+=	-DSNAP

# Uncomment the following line if you want to use Ctrl+Alt+q to kill windows
# instead of Ctrl+Alt+Escape (or just set it to what you want).  This is
# useful under XFree86/Cygwin and VMware (probably)
#CPPFLAGS+=	-DKEY_KILL=XK_q

#CPPFLAGS+=	-DSANITY		# active sanity checks
#CPPFLAGS+=	-DDEBUG			# miscellaneous debugging
#CPPFLAGS+=	-DXDEBUG		# show some X calls

allinone.c: evilwm.h client.c events.c main.c misc.c new.c screen.c
	cat ${.ALLSRC} | sed 's/^#include.*evilwm.*$$//' >$@

.include <bsd.prog.mk>
