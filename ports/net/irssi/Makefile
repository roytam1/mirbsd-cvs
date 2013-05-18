# $MirOS: ports/net/irssi/Makefile,v 1.19 2009/10/24 18:28:24 tg Exp $
# $OpenBSD: Makefile,v 1.24 2004/05/13 07:11:56 pvalchev Exp $

NOT_FOR_PLATFORM=	${NOPIC_PLATFORMS}

COMMENT=		modular IRC client with many features (ipv6, socks, proxy)
DISTNAME=		irssi-0.8.10
DASH_VER=		11
CATEGORIES=		net
MASTER_SITES=		${HOMEPAGE}/files/ \
			http://mirror.irssi.org/ \
			http://nl.irssi.org/files/ \
			http://fi.irssi.org/files/ \
			http://no.irssi.org/files/ \
			http://de.irssi.org/files/ \
			http://uk.irssi.org/files/ \
			http://pl.irssi.org/files/ \
			http://us.irssi.org/files/
HOMEPAGE=		http://www.irssi.org/

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		glib.1.2,gmodule::devel/glib1
RUN_DEPENDS+=		:p5-BSD-arc4random->=1.3:security/p5-BSD-arc4random

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		yes
MODULES+=		p5
CONFIGURE_ARGS+=	--datadir=${PREFIX:Q}/share/doc \
			--enable-perl=yes \
			--enable-ipv6 \
			--with-included-gettext \
			--with-proxy \
			--with-glib1

FLAVOURS=		socks
FLAVOUR?=

.ifndef PERL_VERSION
PERL_VERSION!=		perl -V:version | sed s/[^0-9]//g
.MAKEFLAGS:=		${.MAKEFLAGS} PERL_VERSION=${PERL_VERSION:Q}
.endif

.if ${PERL_VERSION} >= 582
CONFIGURE_ARGS+=	--with-perl-lib=${PREFIX:Q}/libdata/perl5/site_perl
.else
CONFIGURE_ARGS+=	--with-perl-lib=${DESTDIR:Q}${PREFIX:Q}/libdata/perl5/site_perl
.endif
CONFIGURE_ARGS+=	--datadir=${PREFIX:Q}/share/doc \
			--enable-ipv6 \
			--with-proxy \
			--enable-perl=yes \
			--with-included-gettext \
			--with-perl-lib=${PREFIX:Q}/libdata/perl5/site_perl \
			--with-glib1

.if ${FLAVOUR:L:Msocks}
CONFIGURE_ARGS+=	--with-socks
BUILD_DEPENDS+=		::security/dante
.endif

SAMPLE=			default.theme colorless.theme

pre-configure:
	@perl -pi -e 's,doc/irssi,irssi,g' ${WRKSRC}/docs/Makefile.in

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/irssi
	cd ${WRKDIST} && ${INSTALL_DATA} ${SAMPLE} \
	    ${PREFIX}/share/examples/irssi/
	${INSTALL_DATA} ${FILESDIR}/randex.pl ${PREFIX:Q}/share/irssi/scripts/

.include <bsd.port.mk>
