# $OpenBSD: Makefile,v 1.10 2004/04/09 09:52:10 espie Exp $

COMMENT=			simple slang-based menu program

DISTNAME=		pdmenu_1.2.69
PKGNAME=		pdmenu-1.2.69-0
CATEGORIES=     	misc

HOMEPAGE=		http://kitenet.net/programs/pdmenu/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://kitenet.net/programs/code/pdmenu/

LIB_DEPENDS=		slang.14::devel/libslang

FAKE_FLAGS=		INSTALL_PREFIX=${WRKINST}

CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ENV=		SLANG_LIB_LOC=${LOCALBASE}/lib \
			SLANG_H_LOC=${LOCALBASE}/include/slang.h
WRKDIST=		${WRKDIR}/pdmenu

NO_REGRESS=		Yes

.include <bsd.port.mk>
