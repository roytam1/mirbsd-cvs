# $MirOS: ports/net/silc-client/Makefile,v 1.4 2006/02/01 16:28:03 tg Exp $
# $OpenBSD: Makefile,v 1.29 2004/02/19 23:07:27 brad Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=			Secure Internet Live Conferencing (SILC) client
DISTNAME=	silc-client-1.0.1
CATEGORIES=	net

HOMEPAGE=	http://www.silcnet.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://ftp.silcnet.org/client/sources/ \
		ftp://ftp.silcnet.org/silc/client/sources/ \
		http://www.planetmirror.com/pub/silcnet/client/sources/ \
		ftp://ftp.au.silcnet.org/pub/silcnet/client/sources/ \
		http://munitions.vipul.net/software/mirrors/silc/client/sources/ \
		ftp://ftp.no.silcnet.org/pub/silc/client/sources/ \
		http://the.wiretapped.net/security/network-security/silc/client/sources/ \
		ftp://ftp.wiretapped.net/pub/security/network-security/silc/client/sources/

LIB_DEPENDS+=	glib.1.2,gmodule.1.2::devel/glib1

MODULES=	converters/libiconv

CONFDIR=	${SYSCONFDIR}/silc
SUBST_VARS=	CONFDIR

CONFIGURE_STYLE=autoconf
AUTOCONF_NEW=	Yes
MODGNU_CONFIG_GUESS_DIRS= ${WRKSRC} ${WRKSRC}/irssi ${WRKSRC}/lib/silcmath/mpi
CONFIGURE_ARGS+=--enable-ipv6 \
		--with-helpdir=${PREFIX}/share/silc/help \
		--with-docdir=${PREFIX}/share/doc/silc \
		--with-etcdir=${CONFDIR} \
		--with-iconv=${ICONV_PREFIX} \
		--with-perl-lib=${PREFIX}/libdata/perl5/site_perl

CONFIGURE_ENV+=	CFLAGS="" SILC_CFLAGS="${CFLAGS}"

.if ${MACHINE_ARCH} != "i386"
CONFIGURE_ARGS+= --disable-asm
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/silc
	@mv -f ${PREFIX}/share/doc/silc/example_silc.conf \
		${PREFIX}/share/examples/silc/silc.conf
	${INSTALL_DATA} ${WRKSRC}/doc/silcalgs.conf \
		${PREFIX}/share/examples/silc

.include <bsd.port.mk>
