# $MirOS: ports/audio/bonk/Makefile,v 1.1.7.1 2005/03/18 15:42:50 tg Exp $
# $OpenBSD: Makefile,v 1.9 2004/02/25 02:35:15 naddy Exp $

COMMENT=		"lossy/lossless audio coder"

DISTNAME=		bonk-0.6
CATEGORIES=		audio
HOMEPAGE=		http://www.logarithmic.net/pfh/Bonk


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}/

USE_CXX=		Yes
EXTRA_MAKE_FLAGS=	LIBS=-lossaudio
FAKE_FLAGS=		PREFIX='${WRKINST}${PREFIX}' INSTALL='${INSTALL_PROGRAM}'

NO_REGRESS=		Yes

.include <bsd.port.mk>
