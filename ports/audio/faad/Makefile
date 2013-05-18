# $MirOS: ports/audio/faad/Makefile,v 1.5 2008/10/14 19:05:41 tg Exp $
# $OpenBSD: Makefile,v 1.12 2004/04/28 13:05:01 jolan Exp $

COMMENT=		MPEG2 and MPEG-4 AAC decoder
VERSION=		2.0
DASH_VER=		2
DISTNAME=		faad2-${VERSION}
PKGNAME=		faad-${VERSION}-${DASH_VER}
CATEGORIES=    		audio
#MASTER_SITES=		http://users.codefusionis.com/~jolan/
HOMEPAGE=		http://faac.sourceforge.net/

# BSD
PERMIT_PACKAGE_CDROM=	"Patents"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"Patents"
PERMIT_DISTFILES_FTP=	Yes

USE_CXX=	Yes
USE_GMAKE=	Yes
WRKDIST=	${WRKDIR}/faad2

CONFIGURE_STYLE=autogen
AUTOCONF_NEW=	Yes
CONFIGURE_ENV+=	LIBS="-lm"
CONFIGURE_ARGS+=--with-mp4v2

.include <bsd.port.mk>
