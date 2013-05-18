# $MirOS: ports/archivers/mpczar/Makefile,v 1.6 2006/09/14 00:06:49 tg Exp $

COMMENT=		MirPorts CpioZ archiver for distfiles
CATEGORIES=		archivers essentials
DISTNAME=		mpczar-20061119
EXTRACT_SUFX=		.cgz
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/mpczar/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/mpczar
RUN_DEPENDS+=		:paxmirabilis->=20060829:archivers/mircpio

pre-build:
	print '1s!/bin/mksh!${MKSH}!\nwq' | ed -s ${WRKSRC}/mpczar/mpczar.sh

.include <bsd.port.mk>
