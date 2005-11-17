# $MirOS: ports/essentials/cpio/Makefile,v 1.4 2005/11/10 20:44:57 tg Exp $

COMMENT=		"MirPorts CpioZ archiver for distfiles"
CATEGORIES=		archivers essentials
DISTNAME=		mpczar-20051117
EXTRACT_SUFX=		.cgz
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/mir/mpczar/}

# BSD, ISC, MirOS
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/mpczar
RUN_DEPENDS+=		:paxmirabilis->=20051116:essentials/cpio

.include <bsd.port.mk>
