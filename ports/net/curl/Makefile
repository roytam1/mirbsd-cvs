# $MirOS: ports/net/curl/Makefile,v 1.13 2008/08/26 19:16:09 tg Exp $
# $OpenBSD: Makefile,v 1.44 2004/05/18 23:30:45 brad Exp $

COMMENT=		get files from FTP, Gopher, HTTP or HTTPS servers
DISTNAME=		curl-7.18.2
DASH_VER=		1
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

.include <mirports.sys.mk>

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		yes
MODGNU_TYPESCAN=	recv send getnameinfo
CONFIGURE_ENV+=		ac_cv_path_NROFF=${NROFF:Q}
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--enable-http \
			--enable-ftp \
			--enable-file \
			--disable-ldap \
			--disable-ldaps \
			--enable-dict \
			--enable-telnet \
			--enable-tftp \
			--enable-manual \
			--disable-libgcc \
			--enable-ipv6 \
			--enable-nonblocking \
			--enable-thread \
			--disable-ares \
			--enable-verbose \
			--disable-sspi \
			--disable-debug \
			--enable-crypto-auth \
			--enable-cookies \
			--enable-hidden-symbols \
			--without-krb4 \
			--without-spnego \
			--without-gssapi \
			--with-ssl \
			--with-zlib \
			--without-libssh2 \
			--without-gnutls \
			--without-nss \
			--without-ca-bundle \
			--without-libidn

.if !exists(/dev/arandom)
CONFIGURE_ARGS+=	--with-random=/dev/urandom
.else
CONFIGURE_ARGS+=	--with-random=/dev/arandom
.endif

.if ${OStype} == "Interix"
CONFIGURE_ARGS+=	--disable-ipv6
.endif

#XXX suboptimal, better would be to use both or to symlink or flavourise…
.if (${OStype} == "MirBSD") && (${SYSCONFDIR} == "/etc")
CONFIGURE_ARGS+=	--with-ca-path=/etc/ssl/certs
.else
CONFIGURE_ARGS+=	--with-ca-path=${LOCALBASE}/share/ca-certificates
RUN_DEPENDS+=		:ca-certificates->=20080406:essentials/ca-certificates
.endif

.if (${OStype} == "OpenBSD") || (${OStype} == "MidnightBSD")
CONFIGURE_ARGS+=	--with-gssapi
.endif

ALL_TARGET=		all examples

# buggy
#REGRESS_DEPENDS+=	::security/stunnel
REGRESS_TARGET=		test-full
# see mircvs://contrib/code/Snippets/posixtz.c
.if exists(/usr/lib/libposixtz.so)
REGRESS_ENV+=		LD_PRELOAD=/usr/lib/libposixtz.so
.endif

post-extract:
	rm -f ${WRKSRC}/src/hugehelp.c

.include <bsd.port.mk>
