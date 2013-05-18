# $OpenBSD: Makefile,v 1.3 2002/10/28 19:53:44 naddy Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			Western Digital and SMC ethernet card configuration program

DISTNAME=	wdsetup-0.6b
PKGNAME=	wdsetup-0.6b-0
CATEGORIES=	sysutils

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://sunsite.unc.edu/pub/Linux/system/network/drivers/

do-build:
	${_PASS_CC:Q} ${CFLAGS} -o ${WRKSRC}/wdsetup ${WRKSRC}/wdsetup.c -li386

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/wdsetup ${PREFIX}/sbin
	${INSTALL_MAN} ${WRKSRC}/wdsetup.8 ${PREFIX}/man/cat8/wdsetup.0

.include <bsd.port.mk>
