# $MirOS: ports/security/mhash/Makefile,v 1.1.7.1 2005/03/18 15:51:34 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/02/24 19:48:16 naddy Exp $

COMMENT=			strong hash library
DISTNAME=	mhash-0.8.17
CATEGORIES=	security
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=mhash/}
HOMEPAGE=	http://mhash.sourceforge.net/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= autoconf
AUTOCONF_NEW=	 Yes
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static

.include <bsd.port.mk>
