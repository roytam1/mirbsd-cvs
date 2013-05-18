# $MirOS: ports/audio/libcdaudio/Makefile,v 1.1.7.1 2005/03/18 15:42:56 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/12/29 19:29:56 fgsch Exp $

COMMENT=			multi-platform cd player development library
DISTNAME=	libcdaudio-0.99.6
CATEGORIES=	audio
HOMEPAGE=	http://libcdaudio.sourceforge.net/

PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=   ${MASTER_SITE_SOURCEFORGE:=libcdaudio/}

CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static

# Workaround compiler bug with cddb.c, otherwise we get a sig11
.if ${MACHINE_ARCH} == "powerpc"
PATCH_LIST+=	sup-powerpc
.endif

.include <bsd.port.mk>
