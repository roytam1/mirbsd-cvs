# $MirOS: src/distrib/ramtools/init/Makefile,v 1.1 2006/05/15 19:20:16 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/sbin/init

PROG=		init
CPPFLAGS+=	-DDEFAULT_STATE=single_user
DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.include <bsd.prog.mk>
