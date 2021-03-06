# $MirOS: ports/voip/linphone/Makefile,v 1.5 2008/05/07 22:48:44 tg Exp $

COMMENT=			SIP telephony (VoIP) client
CATEGORIES=		comms net voip
_V=			0.12.2
DISTNAME=		linphone-${_V}
HOMEPAGE=		http://www.linphone.org/?lang=us
MASTER_SITES=		http://simon.morlat.free.fr/download/${_V}/source/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

FLAVOURS=		gnome mmx
.if ${MACHINE} == "i386"
FLAVOUR?=		mmx
.else
FLAVOUR?=
.endif

.if ${FLAVOUR:L:Mgnome}
ERRORS+=		"Not yet."
.endif

MODULES=		devel/gettext
LIB_DEPENDS+=		ogg.5::audio/libogg \
			fsmtl.9,osip.9::voip/libosip \
			gmodule-2.0.0.0,gobject-2.0.0.0,gthread-2.0.0.0::devel/glib

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
MODGNU_RECURSE_DIRS=	${WRKSRC}/speex ${WRKSRC}/oRTP ${WRKSRC}/osipua ${WRKSRC}
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

.if !${FLAVOUR:L:Mmmx}
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
