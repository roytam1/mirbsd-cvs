# $MirOS: ports/audio/libsndfile/Makefile,v 1.1.7.1 2005/03/18 15:42:58 tg Exp $
# $OpenBSD: Makefile,v 1.4 2004/02/27 23:35:46 naddy Exp $

COMMENT=			library to handle various audio file formats
DISTNAME=	libsndfile-1.0.7
CATEGORIES=	audio
HOMEPAGE=	http://www.mega-nerd.com/libsndfile/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}

CONFIGURE_STYLE= autoconf
AUTOCONF_NEW= yes
CONFIGURE_ARGS=	${CONFIGURE_SHARED}

# create_symbols_file.sh uses invalid syntax and we don't need this file
pre-build:
	touch ${WRKBUILD}/src/Symbols

.include <bsd.port.mk>
