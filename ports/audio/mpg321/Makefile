# $MirOS$
# $OpenBSD: Makefile,v 1.14 2004/04/05 20:26:25 naddy Exp $

# not very useful with static libao
NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=	"free clone of mpg123, a command-line mp3 player"
DISTNAME=	mpg321-0.2.10
PKGNAME=	${DISTNAME}-1
CATEGORIES=	audio
HOMEPAGE=	http://mpg321.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=mpg321/}

LIB_DEPENDS=	ao::audio/libao \
		id3tag::audio/libid3tag \
		mad::audio/libmad
USE_CXX=	Yes

CONFIGURE_STYLE=gnu
CONFIGURE_ARGS=	--disable-mpg123-symlink

.include <bsd.port.mk>
