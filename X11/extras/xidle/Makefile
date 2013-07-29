# $MirOS: X11/extras/xidle/Makefile,v 1.4 2005/07/21 18:12:10 tg Exp $
# $OpenBSD: Makefile,v 1.4 2005/07/10 21:12:10 matthieu Exp $

PROG=		xidle
CFLAGS+=	-Wall
.if defined(X11LIBDIR) && !empty(X11LIBDIR)
LDADD+=		-L${X11LIBDIR}
.endif
LDADD+=		-lXss -lXext -lX11

.include <bsd.prog.mk>
