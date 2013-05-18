# $MirOS: ports/multimedia/libquicktime/Makefile,v 1.3 2006/02/09 11:12:10 tg Exp $
# $OpenBSD: Makefile,v 1.1.1.1 2004/07/09 07:30:17 sturm Exp $
# $FreeBSD: ports/multimedia/libquicktime/Makefile,v 1.19 2004/03/16 04:23:53 edwin Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			library for reading and writing quicktime files
DISTNAME=		libquicktime-0.9.2
CATEGORIES=		multimedia

HOMEPAGE=		http://libquicktime.sourceforge.net/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=libquicktime/}

LIB_DEPENDS=		vorbis.3,vorbisfile.4,vorbisenc.2::audio/libvorbis \
			jpeg.9::graphics/jpeg \
			dv.4::multimedia/libdv
MODULES+=		graphics/png

USE_GMAKE=		Yes
VMEM_WARNING=		Yes

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS=		--disable-firewire

.include <bsd.port.mk>
