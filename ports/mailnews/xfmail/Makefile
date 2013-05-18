# $MirOS: ports/mailnews/xfmail/Makefile,v 1.5 2008/03/09 17:23:10 tg Exp $
# $OpenBSD: Makefile,v 1.32 2004/01/25 03:24:41 naddy Exp $
# $NetBSD: Makefile,v 1.2 1998/07/04 09:19:04 mycroft Exp $
# $RuOBSD: Makefile,v 1.4 2002/05/18 04:21:36 form Exp $

COMMENT=			xforms-based mail application for Unix
VSN=			1.5.3
DISTNAME=       	xfmail-${VSN}
CATEGORIES=     	mail x11
MASTER_SITES=		ftp://ftp.xfmail.org/pub/xfmail/release/${VSN}/source/
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.xfmail.org/

LIB_DEPENDS=		forms::x11/xforms \
			jpeg.62::graphics/jpeg \
			glib.1.2::devel/glib1

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_CXX=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE=	autogen
CONFIGURE_ARGS=		--without-nas-sound
MODGNU_CONFIG_AUTOGEN=	${WRKSRC}/autogen.sh

FLAVOURS=		esd
FLAVOUR?=

.if ${FLAVOUR:L:Mesd}
CONFIGURE_ARGS+=	--with-esd-sound
LIB_DEPENDS+=		esd.2::audio/esound
.else
CONFIGURE_ARGS+=	--without-esd-sound
.endif

.include <bsd.port.mk>
