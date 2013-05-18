# $MirOS: ports/net/rsync/Makefile,v 1.7 2006/02/09 09:36:11 tg Exp $
# $OpenBSD: Makefile,v 1.41 2004/05/11 13:39:17 naddy Exp $

COMMENT=		"mirroring/synchronisation over low bandwidth links"
DISTNAME=		rsync-2.6.8
CATEGORIES=		net
HOMEPAGE=		http://rsync.samba.org/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

FLAVORS=		static
FLAVOR?=

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
			--with-rsyncd-conf="${SYSCONFDIR}/rsyncd.conf"

.if ${FLAVOR:L} == "static"
# copy this to /var/anoncvs/anoncvs/bin/rsync, chmod 111
CONFIGURE_ENV+=		ac_cv_header_iconv_h=no
LDSTATIC=		-static
.endif

DOCDIR=			${PREFIX}/share/doc/rsync

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/tech_report.tex ${DOCDIR}/

.include <bsd.port.mk>
