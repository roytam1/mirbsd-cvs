# $MirOS: ports/misc/rpm/Makefile,v 1.6 2008/05/07 22:48:32 tg Exp $
# $OpenBSD: Makefile,v 1.11 2002/12/29 19:49:40 fgsch Exp $

#XXX probably i386 platform only

COMMENT=		redhat package manager
DISTNAME=		rpm-3.0.6
DASH_VER=		2
CATEGORIES=		misc archivers emulators

PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes

HOMEPAGE=		http://www.rpm.org/
MASTER_SITES=		ftp://ftp.rpm.org/pub/rpm/dist/rpm-3.0.x/

LIB_DEPENDS+=		bz2::archivers/bzip2 \
			popt::devel/popt

CONFIGURE_STYLE=	autogen
# Enforce check for pgp, so no build-time depend is needed
CONFIGURE_ENV+=		PGPBIN=${LOCALBASE:Q}/bin/pgp
CONFIGURE_ENV+=		varprefix=${LOCALBASE:Q}
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--enable-v5-packages \
			--disable-nls

post-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/db/rpm

.include <bsd.port.mk>
