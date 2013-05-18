# $MirOS: ports/net/mcabber/Makefile,v 1.5 2008/02/27 23:16:20 tg Exp $

COMMENT=		curses-based jabber client implementation
DISTNAME=		mcabber-0.9.6
DASH_VER=		2
CATEGORIES=		net
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.lilotux.net/~mikael/mcabber/
MASTER_SITES=		${HOMEPAGE}files/
RESPONSIBLE=		Jonathan “ciruZ” Schleifer <js@webkeks.org>

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_GMAKE=		Yes
USE_CXX=		Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-gpgme \
			--enable-otr \
			--disable-aspell \
			--with-ssl \
			--disable-hgcset \
			--disable-nls

LIB_DEPENDS+=		glib-2.0.0.800,gmodule-2.0.0.800,gobject-2.0.0.800::devel/glib \
			otr::security/libotr \
			gpgme::security/gpgme

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/mcabber
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/mcabber
	cd ${WRKSRC} && \
	    ${INSTALL_DATA} contrib/themes/*.txt doc/README_PGP.txt README \
	    ${PREFIX}/share/doc/mcabber/ && \
	    ${INSTALL_DATA} mcabberrc.example \
	    ${PREFIX}/share/examples/mcabber/mcabberrc

.include <bsd.port.mk>
