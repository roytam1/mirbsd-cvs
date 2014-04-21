# $MirOS: src/usr.bin/uudecode/Makefile,v 1.2 2005/03/13 18:33:51 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/04/09 22:54:02 millert Exp $

PROG=	uudecode
SRCS=	${PROG}.c
LINKS=	${BINDIR}/uudecode ${BINDIR}/b64decode
NOMAN=	yes

.include <bsd.own.mk>

.if ${MACHINE_OS} == "Linux"
CPPFLAGS+=	-DUSE_LIBBSD
LDADD+=		-lbsd

SRCS+=		base64.c

CPPFLAGS+=	-DL_mbsd_digits_base64
SRCS+=		miscdata.c
.endif

.include <bsd.prog.mk>
