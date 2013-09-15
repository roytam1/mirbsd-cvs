# $MirOS: src/distrib/special/init/Makefile,v 1.5 2013/09/15 11:01:26 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/sbin/init

PROG=		init
CPPFLAGS+=	-DDEFAULT_STATE=single_user
CPPFLAGS+=	-DNORNDSHUF
DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.include <bsd.prog.mk>
