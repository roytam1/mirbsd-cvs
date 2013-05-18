# $MirOS: ports/www/netscape/navigator-linux/Makefile,v 1.4 2005/07/07 21:27:51 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2002/10/29 01:30:42 naddy Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

COMMENT=			Netscape Navigator (linux)

PROGRAM_V=	4.8
V2:=		${PROGRAM_V:S/.//}

DISTNAME=	navigator-v${V2}-us.x86-unknown-linux2.2
PKGNAME=	navigator-linux-${PROGRAM_V}-1
LOCATION=	linux22/navigator_standalone
DIRNAME=	navigator-v${V2}.x86-unknown-linux2.2

NO_BUILD=	Yes
NO_REGRESS=	Yes

.include <bsd.port.mk>
