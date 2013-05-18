# $MirOS: src/distrib/ramtools/init/Makefile,v 1.2 2006/05/26 18:50:30 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/sbin/init

PROG=		init
CPPFLAGS+=	-DDEFAULT_STATE=single_user
DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.include <bsd.prog.mk>
