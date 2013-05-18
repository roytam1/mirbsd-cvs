# $OpenBSD: Makefile,v 1.7 2004/02/01 20:22:18 sturm Exp $

COMMENT=			lightweight and easy to use web calendar

VSN=		2.6
DISTNAME=	calendar-${VSN}
PKGNAME=	mycalendar-${VSN}-${DASH_VER}
CATEGORIES=	www

HOMEPAGE=	http://www.fuzzymonkey.org/newfuzzy/software/perl/


# GPL
PERMIT_PACKAGE_CDROM=  Yes
PERMIT_PACKAGE_FTP=    Yes
PERMIT_DISTFILES_CDROM=Yes
PERMIT_DISTFILES_FTP=  Yes

MASTER_SITES=	http://www.fuzzymonkey.org/files/

NO_BUILD=	Yes
NO_REGRESS=	Yes
PKG_ARCH=	*

WRKDIST=	${WRKDIR}/calendar

PREFIX=		${WWW_PREFIX}
SUBST_VARS+=	WWW_PREFIX
INSTDIR=	${PREFIX}/cgi-bin

do-install:
	${INSTALL_DATA_DIR} ${INSTDIR}/calendar
	@cd ${WRKSRC} && cp -R * ${INSTDIR}/calendar

.include <bsd.port.mk>
