# $MirOS$

PROG=		ssfe
MAN=		ssfe.1
LDADD+=		-ltermcap
DPADD+=		${LIBTERMCAP}
CPPFLAGS+=	-DCONTROL_W -DUSE_TERM

.if defined(DESTDIR) && !empty(DESTDIR) && defined(TRUEPREFIX)
PREFIX:=	${TRUEPREFIX}
.endif
BINDIR=		${PREFIX}/bin
MANDIR=		${PREFIX}/man/cat

.include <bsd.prog.mk>
