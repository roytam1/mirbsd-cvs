# $MirOS: ports/audio/easytag/Makefile,v 1.3 2006/02/09 11:11:03 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/02/08 02:48:13 naddy Exp $

COMMENT=			MP3 ID3 tags editor
DISTNAME=		easytag-0.30
CATEGORIES=		audio x11
HOMEPAGE=		http://easytag.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=easytag/}
EXTRACT_SUFX=		.tar.bz2

PATCHFILES=		patch_easytag_030_030a.diff \
			patch_easytag_030a_030b.diff \
			patch_easytag_030b_030c.diff \
			patch_easytag_030c_030d.diff
PATCH_DIST_STRIP=	-p1

MODULES=		devel/gettext
LIB_DEPENDS=		id3.3.8::audio/id3lib \
			FLAC.4::audio/flac \
			vorbis.1,vorbisfile.1::audio/libvorbis \
			gdk.1.2,gtk.1.2::x11/gtk+1
BUILD_DEPENDS=		:help2man-*:devel/help2man

USE_X11=		Yes
USE_CXX=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	gnu

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/easytag
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/easytag
	${INSTALL_DATA} ${WRKSRC}/USERS-GUIDE ${PREFIX}/share/doc/easytag

.include <bsd.port.mk>
