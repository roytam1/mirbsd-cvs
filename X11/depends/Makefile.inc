# $MirOS: X11/depends/Makefile.inc,v 1.1 2006/06/29 19:36:16 tg Exp $

.ifndef _MODX11_DEPENDS_MAKEFILE_INC
_MODX11_DEPENDS_MAKEFILE_INC=1

X11BASE=	/usr/X11R6
BINDIR=		${X11BASE}/bin
BINGRP=		wheel
MANGRP=		wheel
CFLAGS+=	-I${X11BASE}/include
MANDIR=		${X11BASE}/man/cat
LIBDIR=		${X11BASE}/lib

.endif
