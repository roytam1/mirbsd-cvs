# $MirOS: X11/extras/Makefile.inc,v 1.3 2005/12/05 16:40:14 tg Exp $
# $OpenBSD: Makefile.inc,v 1.3 2004/06/07 20:37:21 matthieu Exp $

.ifndef _MODX11_EXTRAS_MAKEFILE_INC
_MODX11_EXTRAS_MAKEFILE_INC=1

XEXPORTS=	../../xc/exports

X11BASE=	/usr/X11R6
BINDIR=		${X11BASE}/bin
BINGRP=		wheel
MANGRP=		wheel
CFLAGS+=	-I${XEXPORTS}/include -I${X11BASE}/include
LDADD:=		-L${XEXPORTS}/lib ${LDADD}
MANDIR=		${X11BASE}/man/cat
X11LIBDIR=	${X11BASE}/lib

.endif
