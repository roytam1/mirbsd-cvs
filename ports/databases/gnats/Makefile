# $OpenBSD: Makefile,v 1.15 2003/09/01 05:13:17 fgsch Exp $

COMMENT=		GNU Problem Report Management System
DISTNAME=		gnats-3.113.1
DASH_VER=		3
CATEGORIES=		databases devel
HOMEPAGE=		http://www.gnu.org/software/gnats/

# GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=gnats/}
NO_REGRESS=		Yes

CONFIGURE_STYLE=	gnu dest
CONFIGURE_ARGS+=	--with-full-gnats \
			--with-release-based \
			--with-gnats-user=_gnats
CONFIGURE_ENV+=		SEND_PR=$$(whence -p false)

INSTALL_TARGET=	install-gnats install-send-pr install-info

FLAVOURS=	www
FLAVOUR?=

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/gnats/
	sed "s%y0y0y0%${TRUEPREFIX}%g" ${FILESDIR}/README.OpenBSD > \
		${PREFIX}/share/doc/gnats/README.OpenBSD
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/gnats/
	sed "s%/var/lib%${TRUEPREFIX}/share%g" \
		${WRKDIST}/gnats/gnats-db.conf > \
		${PREFIX}/share/examples/gnats/gnats-db.conf
.if ${FLAVOUR:L:Mwww}
	${INSTALL_PROGRAM} ${WRKDIST}/contrib/gnatsweb/gnatsweb.pl \
		${PREFIX}/lib/gnatsweb
	${INSTALL_DATA} ${WRKDIST}/contrib/gnatsweb/gnats.pm \
		${PREFIX}/libdata/perl5/site_perl
.endif

.include <bsd.port.mk>
