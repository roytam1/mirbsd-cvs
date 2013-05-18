# $MirOS: ports/net/ipcheck/Makefile,v 1.3 2006/09/14 00:11:48 tg Exp $
# $OpenBSD: Makefile,v 1.16 2004/02/08 20:47:55 xsa Exp $

COMMENT=			fully compliant DynDNS.org client

MV=			0
VSN=			207
PKGNAME=		ipcheck-${MV}.${VSN}-${DASH_VER}
DISTNAME=		ipcheck.${VSN}
CATEGORIES=		net

HOMEPAGE=		http://ipcheck.sourceforge.net/


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}releases/
EXTRACT_SUFX=
EXTRACT_ONLY=

MODULES=		lang/python

USE_CXX=		Yes
NO_REGRESS=		Yes
NO_BUILD=		Yes
PKG_ARCH=		*
WRKDIST=		${WRKDIR}

do-patch:
	@sed -e "s!/usr/bin/python!${LOCALBASE}/bin/python${MODPY_VERSION}!" \
	     -e "s!ppp0!tun0!" \
	      ${FULLDISTDIR}/${DISTNAME} > ${WRKDIR}/${DISTNAME}

do-install:
	@${INSTALL_SCRIPT} ${WRKDIR}/${DISTNAME} ${PREFIX}/bin/ipcheck.py

.include <bsd.port.mk>
