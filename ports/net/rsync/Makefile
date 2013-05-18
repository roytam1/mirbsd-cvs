# $MirOS: ports/net/rsync/Makefile,v 1.11 2007/09/02 19:55:51 tg Exp $
# $OpenBSD: Makefile,v 1.41 2004/05/11 13:39:17 naddy Exp $

COMMENT=		mirroring/synchronisation over low bandwidth links
DISTNAME=		rsync-2.6.9
CATEGORIES=		net
HOMEPAGE=		http://rsync.samba.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

PATCH_LIST=		patch-* *.diff
DASH_VER=		1

FLAVOURS=		static
FLAVOUR?=

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://rsync.samba.org/ftp/rsync/ \
			http://rsync.samba.org/ftp/rsync/old-versions/

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-included-popt \
			--with-rsh="ssh -T" \
			--with-rsyncd-conf=${SYSCONFDIR:Q}/rsyncd.conf

.if ${FLAVOUR:L} == "static"
# copy this to /var/anoncvs/anoncvs/bin/rsync, chmod 111
CONFIGURE_ENV+=		ac_cv_header_iconv_h=no
CONFIGURE_ARGS+=	--disable-debug \
			--disable-locale
LDSTATIC=		-static
.endif

DOCDIR=			${PREFIX}/share/doc/rsync

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	cd ${WRKSRC}; ${INSTALL_DATA} NEWS OLDNEWS README TODO \
	    tech_report.tex ${DOCDIR}/

.include <bsd.port.mk>
