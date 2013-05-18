# $MirOS$
# $NetBSD: Makefile,v 1.147 2008/06/28 00:13:08 jmcneill Exp $
# $NetBSD: options.mk,v 1.10 2008/06/23 16:57:08 dholland Exp $

ONLY_FOR_PLATFORM=	*:*:amd64 *:*:i386
NOT_FOR_PLATFORM=	Interix:*:*

# warning: this port is most likely prone to pick up hidden dependencies
# warning: this port does not use mirmake.h thus has more strict sysdeps

COMMENT=		Microsoft Windows® 3.1/95/NT emulator for UNIX®
CATEGORIES=		emulators
DISTNAME=		wine-1.0
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://www.winehq.com/

# GNU LGPLv2.1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>

MASTER_SITES=		http://ibiblio.org/pub/linux/system/emulators/wine/ \
			${MASTER_SITE_SOURCEFORGE:=wine/}
EXTRACT_SUFX=		.tar.bz2

#BUILD_DEPENDS+=	fontforge-*::fonts/fontforge
BUILD_DEPENDS+=		bison-*::devel/bison

LIB_DEPENDS+=		jpeg::graphics/jpeg
LIB_DEPENDS+=		xslt::textproc/libxslt
LIB_DEPENDS+=		xml2::textproc/libxml
LIB_DEPENDS+=		dbus-1::sysutils/dbus
LIB_DEPENDS+=		lcms::graphics/lcms
LIB_DEPENDS+=		ungif::graphics/libungif
MODULES+=		graphics/png

DEVOSSAUDIO?=		/dev/audio

VMEM_WARNING=		Yes
USE_CXX=		Yes
USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--without-alsa \
			--without-audioio \
			--without-capi \
			--without-cups \
			--without-esd \
			--without-gphoto \
			--without-hal \
			--without-jack \
			--without-ldap \
			--without-nas \
			--without-sane \
			--without-xcomposite \
			--with-x
CPPFLAGS+=		-pthread
CPPFLAGS+=		-DDEVOSSAUDIO=\"${DEVOSSAUDIO:Q}\"
CPPFLAGS+=		-D_MIRMAKE_H=ignore
LDFLAGS+=		-pthread
COPTS+=			-fno-stack-protector
REGRESS_ENV+=		HOME=${WRKDIR}/homedir

post-extract:
	cd ${FILESDIR} && pax -rw . ${WRKSRC}/
	mkdir -p ${WRKDIR}/homedir

.include <bsd.port.mk>
