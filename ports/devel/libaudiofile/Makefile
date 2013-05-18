# $MirOS: ports/devel/libaudiofile/Makefile,v 1.4 2005/12/28 16:37:56 tg Exp $
# $OpenBSD: Makefile,v 1.28 2004/02/24 23:23:27 brad Exp $

COMMENT=			SGI audiofile library clone
DISTNAME=	audiofile-0.2.6
PKGNAME=	lib${DISTNAME}-1
CATEGORIES=	devel audio
MASTER_SITES=	${MASTER_SITE_GNOME:=sources/audiofile/0.2/}
HOMEPAGE=	http://www.68k.org/~michael/audiofile/

# GPL/LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

AUTOCONF_NEW=		Yes
CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--enable-static

do-regress:
	@cd ${WRKBUILD}/test && \
		${SETENV} ${MAKE_ENV} ${MAKE_PROGRAM} check

.include <bsd.port.mk>
