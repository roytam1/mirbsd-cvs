# $MirOS$
# $OpenBSD: Makefile,v 1.27 2010/11/20 17:22:40 espie Exp $

COMMENT=		network backup solution (client) bacula-fd
VSN=			5.0.3
DISTNAME=		bacula-${VSN}
PKGNAME=		bacula-client-${VSN}-${DASH_VER}
CATEGORIES=		sysutils
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=bacula/}
HOMEPAGE=		http://www.bacula.org/

# AGPLv3 with OpenSSL exception (majority),
# GPLv2 or later, LGPL, permissive, and PD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BACULACONF=		${SYSCONFDIR}/bacula
BACULASTATE=		/var/bacula
SUBST_VARS=		BACULACONF BACULASTATE TRUEPREFIX

CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9
USE_CXX=		Yes
USE_GMAKE=		yes
NO_REGRESS=		yes
MODULES+=		devel/libreadline

CONFIGURE_ARGS+=	--enable-libtool \
			--enable-fast-install \
			--disable-includes \
			--disable-gnome \
			--disable-bat \
			--disable-bwx-console \
			--disable-tray-monitor \
			--enable-smartalloc \
			--enable-client-only \
			--disable-build-dird \
			--disable-build-stored \
			--disable-conio \
			--enable-readline \
			--with-readline=${READLINE_PREFIX:Q} \
			--without-tcp-wrappers \
			--with-openssl \
			--with-working-dir=${BACULASTATE:Q} \
			--with-archivedir=/tmp \
			--with-basename=bacula \
			--with-hostname=bacula \
			--with-scriptdir=${PREFIX:Q}/libexec/bacula \
			--without-dump-email \
			--without-job-email \
			--without-smtp-host \
			--with-pid-dir=/var/run \
			--with-subsys-dir=${BACULASTATE:Q} \
			--with-sbin-perm=0755 \
			--without-x \
			--without-qwt \
			--disable-nls

EXTRA_XAKE_FLAGS+=	NO_ECHO= MKSH=${MKSH:Q}

CONFIGURE_ENV+=		MTX=/bin/chio
CONFIGURE_ENV+=		TAPEDRIVE=/dev/rst0
CONFIGURE_ENV+=		ac_cv_path_MKISOFS=${LOCALBASE:Q}/bin/mkisofs

post-extract:
	mv ${WRKSRC:Q}/autoconf/* ${WRKSRC:Q}/
	rmdir ${WRKSRC:Q}/autoconf
	ln -s . ${WRKSRC:Q}/autoconf
	rm -rf ${WRKSRC:Q}/libtool

post-install:
	mv ${WRKINST:Q}${SYSCONFDIR:Q}/bacula ${PREFIX:Q}/share/examples/

.include <bsd.port.mk>

AUTOCONF_ENV+=		ACLOCAL_FLAGS='-I bacula-macros'
CONFIGURE_ARGS+=	--sysconfdir=${BACULACONF:Q} \
			--localstatedir=${BACULASTATE:Q} \
			--docdir=${PREFIX:Q}/share/doc/bacula \
			--htmldir=${PREFIX:Q}/share/doc/bacula/html
