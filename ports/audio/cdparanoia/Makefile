# $MirOS: ports/audio/cdparanoia/Makefile,v 1.4 2008/10/04 19:02:56 tg Exp $
# $OpenBSD: Makefile,v 1.13 2004/03/02 04:59:51 brad Exp $

COMMENT=			CDDA reading utility with extra data verification features
DISTNAME=	cdparanoia-III-alpha9.8
PKGNAME=	cdparanoia-3.a9.8-0
CATEGORIES=	audio
HOMEPAGE=	http://www.xiph.org/paranoia/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}download/
EXTRACT_SUFX=	.src.tgz

CONFIGURE_STYLE=	autoconf autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ENV=		GCC=${_PASS_CC:T:Q}

NO_REGRESS=		Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/cdparanoia
	${INSTALL_DATA} ${WRKBUILD}/FAQ.txt ${PREFIX}/share/doc/cdparanoia

.include <bsd.port.mk>

.if ${NO_SHARED_LIBS:L} != "no"
ALL_TARGET=	static
INSTALL_TARGET=	sinstall
.endif
