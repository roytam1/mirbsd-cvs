# $MirOS: ports/net/rsync/Makefile,v 1.22 2017/04/04 19:49:31 tg Exp $
# $OpenBSD: Makefile,v 1.77 2016/04/06 21:17:29 sthen Exp $

COMMENT=		mirroring/synchronisation over low bandwidth links
VERSION=		3.1.2
CATEGORIES=		net
HOMEPAGE=		http://rsync.samba.org/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

FLAVOURS=		static
FLAVOUR?=

DISTNAME=		rsync-${VERSION}
FULLPKGNAME=		rsync${FLAVOUR_EXT}-${VERSION}-${DASH_VER}

# GNU GPLv3
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://rsync.samba.org/ftp/rsync/ \
			http://rsync.samba.org/ftp/rsync/old-versions/ \
			http://rsync.samba.org/ftp/rsync/src-previews/ \
			http://ftp.funet.fi/pub/mirrors/samba.org/pub/rsync/src/

# regression tests do more with 'sudo mmake regress'

SUBST_VARS+=		TRUEPREFIX
CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_SCRIPT=	configure.sh
AUTOCONF=		autoconf -o ${CONFIGURE_SCRIPT}
REORDER_DEPENDENCIES+=	rsyncam.dep
CONFIGURE_ENV+=		HAVE_YODL2MAN=0
CONFIGURE_ARGS+=	--with-included-popt \
			--with-rsyncd-conf=${SYSCONFDIR:Q}/rsyncd.conf \
			--with-rsh="ssh -T" \
			--with-nobody-group=_rsync

.if ${FLAVOUR:L} == "static"
CONFIGURE_ENV+=		ac_cv_header_iconv_h=no
CONFIGURE_ARGS+=	--disable-debug \
			--disable-locale \
			--disable-iconv-open \
			--disable-iconv
LDSTATIC=		-static
PLIST=			${PKGDIR}/PLIST-static
.else
MODULES+=		converters/libiconv
USE_ICONV?=		any
USE_ICONV+=		oldm4
.endif

.if ${FLAVOUR:L} == "static"
post-extract:
	@print 'AC_DEFUN([AM_ICONV], [])' >${WRKSRC:Q}/iconv.m4
.endif

post-install:
.if ${FLAVOUR:L} == "static"
	mv -f ${PREFIX:Q}/bin/rsync ${PREFIX:Q}/bin/rsync-static
	-rm -f ${PREFIX:Q}/man/man*/*
.else
	${SUBST_CMD} ${PREFIX:Q}/man/man5/rsyncd.conf.5
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/doc/rsync
	cd ${WRKSRC:Q} && ${INSTALL_DATA} NEWS OLDNEWS README TODO \
	    csprotocol.txt rsync3.txt tech_report.tex doc/rsync.sgml \
	    ${PREFIX:Q}/share/doc/rsync/
.endif

.include <bsd.port.mk>
