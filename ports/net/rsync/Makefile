# $MirOS$
# $OpenBSD: Makefile,v 1.41 2004/05/11 13:39:17 naddy Exp $

COMMENT=	"mirroring/synchronization over low bandwidth links"
DISTNAME=	rsync-2.6.3
CATEGORIES=	net
HOMEPAGE=	http://rsync.samba.org/
RESPONSIBLE=	Thorsten Glaser <tg@${_DOMAIN_DU_JOUR}>

FLAVORS=	static
FLAVOR?=

# GNU GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.samba.org/pub/rsync/ \
		ftp://ftp.samba.org/pub/rsync/old-versions/ \
		http://ftp.samba.org/ftp/rsync/ \
		ftp://ftp.funet.fi/pub/mirrors/rsync.samba.org/pub/rsync/

SEPARATE_BUILD=		simple
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-included-popt \
			--with-rsyncd-conf="${SYSCONFDIR}/rsyncd.conf"
.if ${FLAVOR:L} == "static"
# copy this to /var/anoncvs/anoncvs/usr/bin/rsync, chmod 111
LDSTATIC=		-static
.endif

DOCDIR=			${PREFIX}/share/doc/rsync

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/tech_report.tex ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/rsyncstats ${DOCDIR}

.include <bsd.port.mk>
