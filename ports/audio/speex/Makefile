# $MirOS: ports/audio/speex/Makefile,v 1.2 2005/11/09 20:59:50 bsiegert Exp $
# $OpenBSD: Makefile,v 1.3 2003/11/20 15:54:32 naddy Exp $

COMMENT=			patent-free speech codec

DISTNAME=	speex-1.0.3
PKGNAME=	${DISTNAME}-1
CATEGORIES=	audio
HOMEPAGE=	http://www.speex.org/


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${HOMEPAGE}download/

LIB_DEPENDS=	ogg::audio/libogg

CONFIGURE_STYLE=autoconf no-autoheader
AUTOCONF_NEW=	yes
CONFIGURE_ARGS=	${CONFIGURE_SHARED} \
		--with-ogg-dir=${LOCALBASE}

FAKE_FLAGS=	${DESTDIRNAME}=${WRKINST} \
		docdir=${PREFIX}/share/doc/speex \
		mandir=${PREFIX}/man

.include <bsd.port.mk>
