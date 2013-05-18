# $MirOS: ports/audio/faad/Makefile,v 1.3 2006/06/25 13:07:15 bsiegert Exp $
# $OpenBSD: Makefile,v 1.12 2004/04/28 13:05:01 jolan Exp $

COMMENT=			MPEG2 and MPEG-4 AAC decoder
DISTNAME=	faad2-2.0
PKGNAME=	faad-2.0-1
CATEGORIES=    	audio
MASTER_SITES=	http://users.codefusionis.com/~jolan/
HOMEPAGE=	http://faac.sourceforge.net/

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
