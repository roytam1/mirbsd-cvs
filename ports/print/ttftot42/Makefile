# $MirOS: ports/x11/libxklavier/Makefile,v 1.5 2008/07/27 14:02:44 bsiegert Exp $

COMMENT=		generates Type 42 fonts from TrueType

VERSION=		0.3.1
DISTNAME=		ttftot42-${VERSION}
CATEGORIES=		print graphics

HOMEPAGE=		http://nih.at/ttftot42/
MASTER_SITES=		${HOMEPAGE} http://ftp.giga.or.at/pub/nih/ttftot42/

# ?
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		print/freetype
CPPFLAGS+=		-I${PREFIX:Q}/include/freetype1/freetype

CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes

.include <bsd.port.mk>
