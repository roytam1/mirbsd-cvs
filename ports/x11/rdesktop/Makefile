# $MirOS: ports/x11/rdesktop/Makefile,v 1.3 2007/12/05 19:49:59 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2004/01/22 16:57:18 jcs Exp $

COMMENT=	open source client for RDP and Windows Terminal Server
DISTNAME=	rdesktop-1.8.2
CATEGORIES=	x11 net
MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=rdesktop/}
HOMEPAGE=	http://www.rdesktop.org/

# GNU GPLv3
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MODULES+=		converters/libiconv
NO_REGRESS=		Yes
USE_X11=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-credssp \
			--disable-smartcard \
			--with-x=${X11BASE:Q} \
			--without-sound \
			--with-libiconv-prefix=${ICONV_PREFIX:Q} \
			--with-ipv6

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/rdesktop
	${INSTALL_DATA} \
	    ${WRKSRC}/doc/{keymap-names,keymapping,licensing,redirection}.txt \
	    ${PREFIX}/share/doc/rdesktop/

.include <bsd.port.mk>
