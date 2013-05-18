# $MirOS$
# $OpenBSD: Makefile,v 1.5 2002/12/22 01:49:19 margarida Exp $

COMMENT=		rip audio streams to local files

DISTNAME=		streamripper-1.61.27
CATEGORIES=		audio

HOMEPAGE=		http://streamripper.sourceforge.net/
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=streamripper/}

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		mad::audio/libmad
LIB_DEPENDS+=		ogg::audio/libogg
LIB_DEPENDS+=		vorbis,vorbisfile::audio/libvorbis

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/tre-0.7.2
MODULES+=		converters/libiconv

CONFIGURE_ARGS+=	

post-build:
	nroff -mandoc ${WRKSRC}/streamripper.1 > ${WRKSRC}/streamripper.cat1

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/streamripper ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/streamripper
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/streamripper
	${INSTALL_MAN} ${WRKSRC}/streamripper.cat1 ${PREFIX}/man/cat1/streamripper.0

NO_REGRESS=		Yes

.include <bsd.port.mk>
