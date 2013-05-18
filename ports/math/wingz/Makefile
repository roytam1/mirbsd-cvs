# $MirOS: ports/math/wingz/Makefile,v 1.4 2005/07/07 21:23:29 bsiegert Exp $
# $OpenBSD: Makefile,v 1.18 2002/10/27 18:29:15 naddy Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			commercial spreadsheet

DISTNAME=	Wingz-142
PKGNAME=	${DISTNAME:L}-1
CATEGORIES=	math
EMUL=		linux

MASTER_SITES=	${MASTER_SITE_SUNSITE:=apps/financial/spreadsheet/}
EXTRACT_SUFX=	.tgz

PERMIT_PACKAGE_CDROM=	"shareware"
PERMIT_PACKAGE_FTP=	"shareware"
PERMIT_DISTFILES_CDROM=	"shareware"
PERMIT_DISTFILES_FTP=	Yes

NO_BUILD=	Yes
NO_REGRESS=	Yes

do-configure:
	@cd ${WRKDIST} && \
		sed 's:xxxx:${PREFIX}/lib/X11/:' Wingz/bin/Wingz.sh >Wingz.sh

do-install:
	@cd ${WRKDIST} && pax -w Wingz |(cd ${PREFIX}/lib/X11; pax -r)
	${INSTALL_SCRIPT} ${WRKDIST}/Wingz.sh ${PREFIX}/bin/Wingz
	${INSTALL_DATA} ${WRKDIST}/Wingz/Wingz.Xdefs ${PREFIX}/lib/X11/app-defaults/Wingz
	@install -m 666 /dev/null ${PREFIX}/lib/X11/Wingz/.wingz
	
RUN_DEPENDS=    :redhat_base-*:emulators/redhat/base

WRKDIST=	${WRKDIR}

USE_X11=	Yes

.include <bsd.port.mk>
