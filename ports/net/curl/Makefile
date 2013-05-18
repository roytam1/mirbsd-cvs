# $MirOS: ports/net/curl/Makefile,v 1.9 2007/05/08 21:05:53 tg Exp $
# $OpenBSD: Makefile,v 1.44 2004/05/18 23:30:45 brad Exp $

COMMENT=		get files from FTP, Gopher, HTTP or HTTPS servers
DISTNAME=		curl-7.16.2
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
MODGNU_TYPESCAN=	recv send strdup strstr getnameinfo
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--enable-http \
			--enable-ftp \
			--enable-file \
			--disable-ldap \
			--enable-telnet \
			--enable-tftp \
			--enable-manual \
			--disable-ares \
			--enable-verbose \
			--disable-sspi \
			--enable-crypto-auth \
			--enable-cookies \
			--enable-hidden-symbols \
			--without-krb4 \
			--without-spnego \
			--with-ssl \
			--with-zlib \
			--without-libssh2 \
			--without-gnutls \
			--without-ca-bundle \
			--without-libidn

.include <mirports.sys.mk>

CPPFLAGS+=		-DCURL_CA_PATH=\"${SYSCONFDIR}/ssl/certs\"

.if !exists(/dev/arandom)
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
