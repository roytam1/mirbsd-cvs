# $MirOS: ports/audio/esound/Makefile,v 1.4 2006/02/09 09:35:36 tg Exp $
# $OpenBSD: Makefile,v 1.34 2004/11/21 17:51:44 espie Exp $
# $FreeBSD: Makefile,v 1.8 1999/03/09 01:08:46 nectar Exp $

COMMENT=			sound library for Enlightenment

DISTNAME=	esound-0.2.34
PKGNAME=	${DISTNAME}-2
CATEGORIES=	audio
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/esound/0.2/}

HOMEPAGE=	http://www.tux.org/~ricdude/EsounD.html

LIB_DEPENDS=	audiofile::devel/libaudiofile

# GPL/LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= autoconf
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --with-libwrap
# broken, relies upon v4-mapped addresses
CONFIGURE_ARGS+= --disable-ipv6

post-extract:
	@cp -f ${FILESDIR}/audio_sun.c ${WRKSRC}

.include <bsd.port.mk>
