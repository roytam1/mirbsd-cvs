# $MirOS: ports/security/pwgen/Makefile,v 1.3 2006/09/14 00:13:17 tg Exp $
# $OpenBSD: Makefile,v 1.2 2004/04/18 06:41:11 robert Exp $

COMMENT=		simple password generator
DISTNAME=		pwgen-2.03
DASH_VER=		1
CATEGORIES=		security
HOMEPAGE=		http://sourceforge.net/projects/pwgen/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=pwgen/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
MAKE_FLAGS=		WALL_OPTS=""

NO_REGRESS=		Yes

pre-configure:
	@rm ${WRKSRC}/config.cache

.include <bsd.port.mk>
