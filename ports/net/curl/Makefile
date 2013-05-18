# $MirOS: ports/net/curl/Makefile,v 1.5 2006/07/23 16:41:47 tg Exp $
# $OpenBSD: Makefile,v 1.44 2004/05/18 23:30:45 brad Exp $

COMMENT=			get files from FTP, Gopher, HTTP or HTTPS servers
DISTNAME=		curl-7.15.4
CATEGORIES=		net
MASTER_SITES=		http://curl.haxx.se/download/ \
			ftp://ftp.sunet.se/pub/www/utilities/curl/ \
			ftp://cool.haxx.se/curl/ \
			ftp://ftp.fu-berlin.de/pub/unix/network/curl/ \
			http://curl.linuxworx.com.au/ \
			http://www.cubic.ch/mirror/curl/ \
			http://curl.webmeta.com/ \
			ftp://gd.tuwien.ac.ut/utils/archivers/curl/
HOMEPAGE=		http://curl.haxx.se/

# MIT
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		yes
CONFIGURE_ARGS+=	${CONFIGURE_SHARED}
CONFIGURE_ARGS+=	--with-random="/dev/arandom" \
			--disable-dependency-tracking \
			--disable-libtool-lock \
			--enable-http \
			--enable-ftp \
			--enable-file \
			--enable-tftp \
			--disable-ldap \
			--enable-gopher \
			--enable-telnet \
			--enable-manual \
			--enable-cookies \
			--enable-crypto-auth \
			--with-ssl \
			--with-zlib \
			--without-ca-bundle \
			--without-libidn \
			--disable-libtool-lock

.include <mirports.sys.mk>
.if ${OStype} == "OpenBSD"
CONFIGURE_ARGS+=	--with-gssapi
.else
CONFIGURE_ARGS+=	--without-gssapi
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/emacs/site-lisp
	cd ${WRKSRC}; ${INSTALL_DATA} curl-style.el \
	    ${PREFIX}/share/emacs/site-lisp/

.include <bsd.port.mk>
