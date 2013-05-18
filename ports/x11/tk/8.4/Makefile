# $MirOS: ports/x11/tk/8.4/Makefile,v 1.5 2006/11/20 22:50:49 tg Exp $
# $OpenBSD: Makefile,v 1.6 2004/05/07 15:28:32 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=		graphical toolkit for Tcl
VERSION=		8.4.14
DISTNAME=		tk${VERSION}-src
PKGNAME=		tk-${VERSION}-0
CATEGORIES=		x11 x11/tk
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=tcl/}
HOMEPAGE=		http://www.tcl.tk/

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

LIB_DEPENDS+=		tcl84:tcl-8.4.*:lang/tcl/8.4

FAKE_FLAGS=	INSTALL="install -c" INSTALL_ROOT="${WRKINST}" \
		BASE_INCLUDE_DIR='$$(prefix)/include/tk$$(VERSION)' \
		INCLUDE_INSTALL_DIR='$$(INSTALL_ROOT)$$(BASE_INCLUDE_DIR)' \
		GENERIC_INCLUDE_INSTALL_DIR='$$(BASE_INCLUDE_DIR)/generic' \
		UNIX_INCLUDE_INSTALL_DIR='$$(BASE_INCLUDE_DIR)/unix' \
		MAN_INSTALL_DIR='$${INSTALL_ROOT}$$(TK_LIBRARY)/man'

USE_X11=		Yes
CONFIGURE_STYLE=	autoconf no-autoheader
CONFIGURE_ARGS+=	${CONFIGURE_SHARED} \
			--enable-static \
			--with-tcl=${LOCALBASE:Q}/lib/tcl8.4
CONFIGURE_ENV+=		PORTSDIR="${PORTSDIR}"

WRKDIST=		${WRKDIR}/tk${VERSION}
WRKSRC=			${WRKDIST}/unix

REGRESS_TARGET=		test
REGRESS_DEPENDS+=	::lang/tcl/8.4:regress
REGRESS_FLAGS=		TCL_BIN_DIR=$$(cd ${PORTSDIR}/lang/tcl/8.4 && \
			    ${MAKE} show=WRKBUILD)
# This regression test wants an X11 display
REGRESS_FLAGS+=		DISPLAY=${DISPLAY} XAUTHORITY=${XAUTHORITY}
REGRESS_IS_INTERACTIVE=	Yes

post-install:
.ifndef DEBUG
	@strip ${PREFIX}/bin/wish8.4
.endif

.include <bsd.port.mk>
