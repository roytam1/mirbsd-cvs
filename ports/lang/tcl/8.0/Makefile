# $OpenBSD: Makefile,v 1.12 2002/12/29 20:41:08 fgsch Exp $
# $FreeBSD: Makefile,v 1.4 1997/12/01 16:50:49 pst Exp $

COMMENT=			Tool Command Language

DISTNAME=	tcl8.0.5
PKGNAME=	tcl-8.0.5-0
CATEGORIES=	lang lang/tcl
MASTER_SITES=	${MASTER_SITE_TCLTK:=tcl8_0/}

HOMEPAGE=	http://dev.scriptics.com/software/tcltk/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FAKE_FLAGS=	INSTALL="install -c" INSTALL_ROOT="${WRKINST}" \
		BASE_INCLUDE_DIR='$$(prefix)/include/tcl$$(VERSION)' \
		INCLUDE_INSTALL_DIR='$$(INSTALL_ROOT)$$(BASE_INCLUDE_DIR)' \
		GENERIC_INCLUDE_INSTALL_DIR='$$(BASE_INCLUDE_DIR)/generic' \
		UNIX_INCLUDE_INSTALL_DIR='$$(BASE_INCLUDE_DIR)/unix' \
		MAN_INSTALL_DIR='$${INSTALL_ROOT}$$(TCL_LIBRARY)/man'

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS+= ${CONFIGURE_SHARED}
CONFIGURE_ARGS+= --enable-static

.if (${MACHINE_ARCH} == "mips")
CONFIGURE_ARGS+= --disable-load
.endif
CONFIGURE_ENV=  PORTSDIR="${PORTSDIR}"

WRKDIST=	${WRKDIR}/${DISTNAME}/unix
REGRESS_TARGET=	test
TESTHOME=${WRKDIR}/testhome
REGRESS_FLAGS=	HOME=${TESTHOME}
# Needs a full network connection to run
REGRESS_IS_INTERACTIVE=Yes
pre-regress:
	mkdir -p ${TESTHOME}

post-install:
	@strip ${PREFIX}/bin/tclsh8.0

.include <bsd.port.mk>
