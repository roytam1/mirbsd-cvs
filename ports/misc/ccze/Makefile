# $MirOS: ports/misc/ccze/Makefile,v 1.2 2005/07/07 21:23:35 bsiegert Exp $
# $OpenBSD: Makefile,v 1.4 2004/04/18 06:41:11 robert Exp $

COMMENT=			log colorizer

DISTNAME=		ccze-0.2.1	
PKGNAME=		${DISTNAME}-1
CATEGORIES=		misc

RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

HOMEPAGE=		http://bonehunter.rulez.org/CCZE.phtml

MASTER_SITES=		ftp://bonehunter.rulez.org/pub/ccze/stable/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS=		pcreposix,pcre::devel/pcre

USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		--with-builtins=all

.include <bsd.port.mk>
