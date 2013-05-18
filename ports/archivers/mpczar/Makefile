# $MirOS: ports/archivers/mpczar/Makefile,v 1.8 2008/11/01 22:57:21 tg Exp $

COMMENT=		MirPorts CpioZ archiver for distfiles
CATEGORIES=		archivers essentials
DISTNAME=		mpczar-20091122
EXTRACT_SUFX=		.cpio.gz
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/mpczar/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/mpczar
RUN_DEPENDS+=		:paxmirabilis->=20091122:archivers/mircpio

pre-build:
	print '1s!/bin/mksh!'${MKSH:Q}'!\nwq' | ed -s ${WRKSRC}/mpczar/mpczar.sh

.include <bsd.port.mk>
