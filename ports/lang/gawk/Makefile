# $MirOS$
# $OpenBSD: Makefile,v 1.6 2004/02/01 12:54:15 wilfried Exp $

COMMENT=		GNU awk
DISTNAME=		gawk-${VERSION}
VERSION=		3.1.3
DASH_VER=		1
CATEGORIES=		lang
HOMEPAGE=		http://www.gnu.org/software/gawk/gawk.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=gawk/}

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-nls
SUBST_VARS+=		VERSION

.include <bsd.port.mk>
