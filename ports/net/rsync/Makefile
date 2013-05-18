# $MirOS: ports/net/rsync/Makefile,v 1.12 2008/03/09 17:23:22 tg Exp $
# $OpenBSD: Makefile,v 1.41 2004/05/11 13:39:17 naddy Exp $

COMMENT=		mirroring/synchronisation over low bandwidth links
DISTNAME=		rsync-3.0.1pre3
CATEGORIES=		net
HOMEPAGE=		http://rsync.samba.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

FLAVOURS=		static
FLAVOUR?=

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
# copy this to /var/anoncvs/anoncvs/bin/rsync, chmod 111
CONFIGURE_ENV+=		ac_cv_header_iconv_h=no
CONFIGURE_ARGS+=	--disable-debug \
			--disable-iconv \
			--disable-locale
LDSTATIC=		-static
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
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/rsync
	cd ${WRKSRC} && ${INSTALL_DATA} COPYING NEWS OLDNEWS README TODO \
	    csprotocol.txt rsync3.txt rsyncsh.txt tech_report.tex \
	    ${PREFIX}/share/doc/rsync/

.include <bsd.port.mk>
