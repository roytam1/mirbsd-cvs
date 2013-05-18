# $MirOS: ports/net/rsync/Makefile,v 1.20 2009/05/17 17:51:07 tg Exp $
# $OpenBSD: Makefile,v 1.41 2004/05/11 13:39:17 naddy Exp $

COMMENT=		mirroring/synchronisation over low bandwidth links
VERSION=		3.0.9
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
			http://rsync.samba.org/ftp/rsync/src-previews/

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_SCRIPT=	configure.sh
AUTOCONF=		autoconf -o ${CONFIGURE_SCRIPT}
REORDER_DEPENDENCIES+=	rsyncam.dep
CONFIGURE_ARGS+=	--with-included-popt \
			--with-rsh="ssh -T" \
			--with-rsyncd-conf=${SYSCONFDIR:Q}/rsyncd.conf

.if ${FLAVOUR:L} == "static"
CONFIGURE_ENV+=		ac_cv_header_iconv_h=no
CONFIGURE_ARGS+=	--disable-debug \
			--disable-iconv \
			--disable-iconv-open \
			--disable-locale
LDSTATIC=		-static
PLIST=			${PKGDIR}/PLIST-static
.else
MODULES+=		converters/libiconv
USE_ICONV?=		any
USE_ICONV+=		oldm4
.endif

.if ${FLAVOUR:L} == "static"
post-extract:
	@print 'AC_DEFUN([AM_ICONV], [])' >${WRKSRC}/iconv.m4
.endif

post-install:
.if ${FLAVOUR:L} == "static"
	mv -f ${PREFIX}/bin/rsync ${PREFIX}/bin/rsync-static
	-rm -f ${PREFIX}/man/man*/*
.else
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/rsync
	cd ${WRKSRC} && ${INSTALL_DATA} NEWS OLDNEWS README TODO rsync3.txt \
	    csprotocol.txt tech_report.tex ${PREFIX}/share/doc/rsync/
.endif

.include <bsd.port.mk>
