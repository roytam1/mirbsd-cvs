# $MirOS: ports/editors/nano/Makefile,v 1.5 2008/03/09 20:13:11 tg Exp $
# $OpenBSD: Makefile,v 1.36 2004/02/20 21:30:38 naddy Exp $

COMMENT=		free Pico clone with some new features
RESPONSIBLE=		Andreas Gockel <miros@unixforge.de>
DISTNAME=		nano-2.0.7
CATEGORIES=		editors
HOMEPAGE=		http://www.nano-editor.org/
MASTER_SITES=		${HOMEPAGE}dist/v2.0/

# GPLv3
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		devel/libncursesw
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--enable-all \
			--enable-utf8 \
			--disable-nls

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/nano
	${INSTALL_DATA} ${WRKSRC}/doc/nanorc.sample \
	    ${PREFIX}/share/examples/nano/

.include <bsd.port.mk>
