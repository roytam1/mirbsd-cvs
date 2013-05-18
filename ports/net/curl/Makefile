# $MirOS: ports/net/curl/Makefile,v 1.6 2006/09/14 00:11:37 tg Exp $
# $OpenBSD: Makefile,v 1.44 2004/05/18 23:30:45 brad Exp $

COMMENT=		get files from FTP, Gopher, HTTP or HTTPS servers
DISTNAME=		curl-7.15.5
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
CONFIGURE_ARGS+=	--disable-dependency-tracking \
			${CONFIGURE_SHARED} \
			--enable-static \
			--disable-libtool-lock \
			--enable-http \
			--enable-ftp \
			--enable-file \
			--disable-ldap \
			--enable-telnet \
			--enable-tftp \
			--enable-manual \
			--enable-verbose \
			--enable-crypto-auth \
			--enable-cookies \
			--enable-hidden-symbols \
			--without-krb4 \
			--with-ssl \
			--without-gnutls \
			--without-ca-bundle \
			--with-zlib \
			--without-libidn

.include <mirports.sys.mk>

.if (${OStype} == "Darwin") || (${OStype} == "Interix")
CONFIGURE_ARGS+=	--with-random=/dev/urandom
.else
CONFIGURE_ARGS+=	--with-random=/dev/arandom
.endif

.if ${OStype} == "Interix"
CONFIGURE_ARGS+=	--disable-ipv6
.else
CONFIGURE_ARGS+=	--enable-ipv6
.endif

.if ${OStype} == "OpenBSD"
CONFIGURE_ARGS+=	--with-gssapi
.else
CONFIGURE_ARGS+=	--without-gssapi
.endif

.include <bsd.port.mk>
