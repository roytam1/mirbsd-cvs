# $MirOS: ports/net/mcabber/Makefile,v 1.10 2008/10/09 21:01:33 tg Exp $

COMMENT=		curses-based jabber client implementation
DISTNAME=		mcabber-0.9.9
CATEGORIES=		net
EXTRACT_SUFX=		.tar.bz2
HOMEPAGE=		http://www.lilotux.net/~mikael/mcabber/
MASTER_SITES=		${HOMEPAGE}files/ \
			http://mcabber.com/files/

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

LIB_DEPENDS+=		glib-2.0.0.0,gmodule-2.0.0.0,gobject-2.0.0.0::devel/glib \
			otr:libotr->=3.1.0:security/libotr \
			gcrypt:libgcrypt->=1.2.2:security/libgcrypt \
			gpgme:gpgme->=1.0.0:security/gpgme
MODULES+=		devel/pkgconfig
MODULES+=		devel/libncursesw

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/{doc,examples}/mcabber
	cd ${WRKSRC} && \
	    ${INSTALL_DATA} contrib/themes/*.txt doc/README_PGP.txt README \
	    ${PREFIX}/share/doc/mcabber/ && \
	    ${INSTALL_DATA} mcabberrc.example \
	    ${PREFIX}/share/examples/mcabber/mcabberrc
	mv ${PREFIX}/man/man1/mcabber.1 ${PREFIX}/man/man1/mcabber.tbl

.include <bsd.port.mk>
