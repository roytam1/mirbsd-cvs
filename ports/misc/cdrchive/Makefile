# $MirOS: ports/misc/cdrchive/Makefile,v 1.4 2006/02/09 13:25:14 tg Exp $
# $OpenBSD: Makefile,v 1.10 2004/02/25 02:35:16 naddy Exp $

BROKEN=			Missing support for module x11/qt2

COMMENT=			Qt-based CD creation tool

PKGNAME=		${DISTNAME:S/-OpenBSD//}-0
DISTNAME=		cdrchive-1.0.1-OpenBSD
CATEGORIES=		misc x11
HOMEPAGE=		http://www.drahthaar.clara.net/cdr.htm

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://www.drahthaar.clara.net/ \
			http://www.jakemsr.com/openbsd/ports/

#MODULES=		x11/qt2

RUN_DEPENDS=		:cdrtools-*:sysutils/cdrtools


CONFIGURE_STYLE=	autoconf
CONFIGURE_ARGS=		--datadir=${PREFIX}/share/doc/cdrchive \
			--x-includes=${X11BASE}/include \
			--x-libraries=${X11BASE}/lib \
			--with-extra-includes=${LOCALBASE}/include \
			--with-extra-libs=${LOCALBASE}/lib \
			${MODQT_CONFIGURE_ARGS}
MAKE_FLAGS=		CFLAGS="${CXXFLAGS} -c" CLFLAGS=""

WRKDIST=		${WRKDIR}/cdr-bsd

NO_REGRESS=		Yes

post-install:
		${INSTALL_DATA_DIR} ${PREFIX}/share/examples/cdrchive
		${INSTALL_DATA} ${WRKBUILD}/cdr.conf \
			${PREFIX}/share/examples/cdrchive/cdr.conf.sample

.include <bsd.port.mk>
