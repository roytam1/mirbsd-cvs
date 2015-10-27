# $MirOS: ports/audio/lame/Makefile,v 1.6 2008/03/09 17:22:24 tg Exp $
# $OpenBSD: Makefile,v 1.26 2005/12/23 15:03:07 espie Exp $

COMMENT=		lame ain't an MP3 encoder
VERSION=		3.96.1
DISTNAME=		lame-${VERSION}
CATEGORIES=		audio
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=lame/}
HOMEPAGE=		http://www.mp3dev.org/

PERMIT_PACKAGE_CDROM=	MP3 patent, http://mp3licensing.com/royalty/swenc.html
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	MP3 patent, http://mp3licensing.com/royalty/swenc.html
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=		Yes
# WARNING: automake breaks
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes

FLAVOURS=		no_x11
FLAVOUR?=

CONFIGURE_ARGS+=	--enable-mp3rtp
EXTRA_MAKE_FLAGS+=	pkghtmldir=${TRUEPREFIX}/share/doc/lame

.if ${MACHINE_ARCH} == "i386"
BUILD_DEPENDS+=		nasm::lang/nasm
CONFIGURE_ARGS+=	--enable-nasm
.else
CONFIGURE_ARGS+=	--disable-nasm
.endif

.if ${FLAVOUR:L} != "no_x11"
USE_X11=		Yes
CONFIGURE_ARGS+=	--enable-mp3x \
			--with-gtk-prefix=${LOCALBASE}
LIB_DEPENDS+=		gtk.1.2,gdk.1.2::x11/gtk+1
.endif

.include <bsd.port.mk>
