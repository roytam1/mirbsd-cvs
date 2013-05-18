# $MirOS: ports/voip/linphone/Makefile,v 1.2 2005/09/01 20:59:17 tg Exp $

COMMENT=			SIP telephony (VoIP) client
CATEGORIES=		comms net voip
_V=			0.12.2
DISTNAME=		linphone-${_V}
HOMEPAGE=		http://www.linphone.org/?lang=us
MASTER_SITES=		http://simon.morlat.free.fr/download/${_V}/source/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# GNU GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

FLAVORS=		gnome mmx
.if ${MACHINE} == "i386"
FLAVOR?=		mmx
.else
FLAVOR?=
.endif

.if ${FLAVOR:L:Mgnome}
ERRORS+=		"Not yet."
.endif

MODULES=		devel/gettext
LIB_DEPENDS+=		ogg.5::audio/libogg \
			fsmtl.9,osip.9::voip/libosip \
			gmodule-2.0.0.0,gobject-2.0.0.0,gthread-2.0.0.0::devel/glib

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/speex \
			  ${WRKSRC}/oRTP ${WRKSRC}/osipua
CONFIGURE_ARGS+=	--enable-glib \
			--disable-gnome_ui \
			--disable-alsa \
			--disable-ipv6 \
			--disable-truespeech \
			--disable-video \
			--with-osip=${LOCALBASE} \
			--with-speex=embedded \
			${CONFIGURE_SHARED}
USE_GMAKE=		Yes

.if !${FLAVOR:L:Mmmx}
CONFIGURE_ARGS+=	--disable-mmx
.endif

.include <mirports.sys.mk>
CFLAGS+=		-pthread
LDFLAGS+=		-pthread

post-extract:
	@rm -f ${WRKSRC}/ffmpeg/{,libavcodec/}Makefile.orig

post-install:
	@mv ${PREFIX}/share/man/man1/* ${PREFIX}/man/man1/
	@rm -rf ${PREFIX}/share/man

.include <bsd.port.mk>
