# $MirOS: ports/audio/gom/Makefile,v 1.2 2006/02/09 09:35:36 tg Exp $
# $OpenBSD: Makefile,v 1.16 2002/12/29 19:29:56 fgsch Exp $

COMMENT=			generic audio mixer
DISTNAME=	gom-0.30.0
CATEGORIES=     audio
MASTER_SITES=	ftp://ibiblio.org/pub/linux/apps/sound/mixers/ \
		http://home.t-online.de/home/absurder/code/c/gom/
HOMEPAGE=	http://home.t-online.de/home/absurder/code/c/gom/gom.en.html

# License: GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=	no_x11
FLAVOR?=

AUTOCONF_NEW=	Yes
CONFIGURE_STYLE=autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+= --disable-x-gomii
.else
CONFIGURE_ARGS+= --enable-x-gomii
USE_X11=	Yes
LIB_DEPENDS=	xview::x11/xview/lib \
		olgx::x11/xview/lib
.endif

.include <bsd.port.mk>
