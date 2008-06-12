# $MirOS$

PROG=		mount_vnd
MAN=		${PROG}.8
LINKS+=		${BINDIR}/${PROG} ${BINDIR}/vnconfig
MLINKS+=	${PROG}.8 vnconfig.8

DPADD+=		${LIBUTIL}
LDADD+=		-lutil

.if defined(SMALL) && ${SMALL:L} != "no"
CPPFLAGS+=	-DSMALL
.else
DPADD+=		${LIBCRYPTO}
LDADD+=		-lcrypto
.endif

.include <bsd.prog.mk>
