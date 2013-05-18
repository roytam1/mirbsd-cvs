# $MirOS: src/sys/arch/i386/stand/installboot/Makefile,v 1.2 2005/03/06 21:27:04 tg Exp $
# $OpenBSD: Makefile,v 1.9 2000/06/08 00:56:07 mickey Exp $

MAN=	installboot.8

.if ${MACHINE_ARCH} == "i386"
PROG=	installboot

LDADD=	-lutil
DPADD=	${LIBUTIL}
# Need this to work in the miniroot
LDSTATIC=	-static

SADIR=	${.CURDIR}/..
.else
NOPROG=	yes
.endif

.include <bsd.prog.mk>
