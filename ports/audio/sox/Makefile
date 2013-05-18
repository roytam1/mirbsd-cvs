# $MirOS: ports/audio/sox/Makefile,v 1.2 2005/06/05 19:03:21 bsiegert Exp $
# $OpenBSD: Makefile,v 1.31 2005/05/15 19:40:36 naddy Exp $

COMMENT=			SOund eXchange - universal sound sample translator

DISTNAME=	sox-12.17.7
CATEGORIES=	audio
HOMEPAGE=	http://sox.sourceforge.net/


# gsm library has bad license
PERMIT_PACKAGE_CDROM=	"no redistribution"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no redistribution"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www.cnpbagwell.com/ \
		${MASTER_SITE_SOURCEFORGE:=sox/}

CONFIGURE_STYLE=gnu dest
CONFIGURE_ARGS=	--disable-oss-dsp

FLAVORS=	mp3 vorbis
FLAVOR?=

.if ${FLAVOR:L:Mvorbis}
LIB_DEPENDS+=	vorbis.1,vorbisenc.1,vorbisfile.2::audio/libvorbis
.else
CONFIGURE_ARGS+= --disable-ogg-vorbis
.endif

.if ${FLAVOR:L:Mmp3}
LIB_DEPENDS+=	mad.2::audio/libmad mp3lame.0::audio/lame
.else
CONFIGURE_ARGS+= --disable-mad --disable-lame
.endif

do-regress:
	@cd ${WRKSRC}/src && ./tests.sh && ./testall.sh

.include <bsd.port.mk>
