# $MirOS: ports/graphics/gimp/Makefile,v 1.3 2006/02/09 11:11:46 tg Exp $
# $OpenBSD: Makefile,v 1.6 2005/07/08 07:50:55 fgsch Exp $

BROKEN=		porting in progress

COMMENT=			GNU Image Manipulation Program
DISTNAME=	gimp-2.2.8
CATEGORIES=	graphics
DIR=		gimp/v2.2
HOMEPAGE=	http://www.gimp.org/
MASTER_SITES=	ftp://ftp.gimp.org/pub/${DIR}/ \
		ftp://ftp.sunet.se/pub/gnu/${DIR}/ \
		ftp://ftp.cs.umn.edu/pub/${DIR}/ \
		ftp://ftp.funet.fi/pub/sci/graphics/packages/gimp/${DIR}/

BUILD_DEPENDS=	:p5-XML-Parser-*:textproc/p5-XML-Parser
RUN_DEPENDS=    :wget-*:net/wget
LIB_DEPENDS=	gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+ \
		aa.1.3::graphics/aalib \
		art_lgpl_2.5::graphics/libart \
		exif::graphics/libexif \
		mng::graphics/libmng \
		tiff.35::graphics/tiff \
		wmf.6,wmflite.6::graphics/libwmf

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES=	devel/gettext devel/pkgconfig graphics/png

USE_X11=	Yes
USE_GMAKE=	Yes
CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
CONFIGURE_ARGS=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --disable-print --disable-gtkhtml --disable-svg \
		 --disable-sse

FLAVORS=	altivec
FLAVOR?=

.if ${FLAVOR:L} == "altivec"
ONLY_FOR_PLATFORM=	*:*:powerpc
CONFIGURE_ARGS+= --enable-altivec
.else
CONFIGURE_ARGS+= --disable-altivec
.endif

.if ${MACHINE_ARCH} == "i386" || ${MACHINE} == "amd64"
CONFIGURE_ARGS+= --enable-mmx
.endif

.include <bsd.port.mk>
