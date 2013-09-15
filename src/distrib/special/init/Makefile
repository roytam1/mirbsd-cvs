# $MirOS: src/distrib/special/init/Makefile,v 1.4 2006/08/17 20:13:28 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/sbin/init

PROG=		init
CPPFLAGS+=	-DDEFAULT_STATE=single_user
DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.if ${MACHINE_ARCH} == "sparc"
CPPFLAGS+=	-DNORNDSHUF
.endif

.include <bsd.prog.mk>
