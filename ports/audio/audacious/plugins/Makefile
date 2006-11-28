# $MirOS: ports/audio/audacious/plugins/Makefile,v 1.1 2006/11/25 23:21:54 bsiegert Exp $

COMMENT=		plugins package for audacious
DISTNAME=		audacious-plugins-1.2.5
PKGNAME=		${DISTNAME}-1
CATEGORIES=		audio

LIB_DEPENDS+=		audacious.4.0::audio/audacious/player
LIB_DEPENDS+=		gdk-x11-2.0.0.0,gdk_pixbuf-2.0.0.0,gtk-x11-2.0.0.0::x11/gtk+
LIB_DEPENDS+=		glade-2.0.0.0::devel/libglade
LIB_DEPENDS+=		tag,tag_c::audio/taglib
LIB_DEPENDS+=		ogg::audio/libogg
LIB_DEPENDS+=		vorbis,vorbisfile::audio/libvorbis
LIB_DEPENDS+=		nemesi::audio/libnms
LIB_DEPENDS+=		FLAC::audio/flac
LIB_DEPENDS+=		SDL::devel/sdl
LIB_DEPENDS+=		audiofile::devel/libaudiofile
LIB_DEPENDS+=		curl::net/curl

CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-ipv6
CONFIGURE_ARGS+=	--disable-dependency-tracking
CONFIGURE_ARGS+=	--disable-pulse
CONFIGURE_ARGS+=	--disable-lirc
CONFIGURE_ARGS+=	--disable-modplug
CONFIGURE_ARGS+=	--disable-alsa
CONFIGURE_ARGS+=	--disable-amidiplug
CONFIGURE_ARGS+=	--disable-timidity
CONFIGURE_ARGS+=	--with-dev-dsp=/dev/sound

.include <bsd.port.mk>
