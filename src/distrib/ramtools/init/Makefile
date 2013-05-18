# $MirOS$

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/sbin/init
.PATH: ${SRC_PATH}

PROG=		init
NOMAN=		yes
CPPFLAGS+=	-DDEFAULT_STATE=single_user
DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.include <bsd.prog.mk>
