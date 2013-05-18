# $MirOS: ports/audio/liba52/Makefile,v 1.2 2005/07/07 21:17:16 bsiegert Exp $
# $OpenBSD: Makefile,v 1.6 2004/02/23 00:33:34 naddy Exp $

CATEGORIES=	audio
COMMENT=			AC-3 decoding library
DISTNAME=	a52dec-0.7.4
PKGNAME=	liba52-0.7.4-1
MASTER_SITES=	http://liba52.sourceforge.net/files/
HOMEPAGE=	http://liba52.sourceforge.net/

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <bsd.port.mk>
