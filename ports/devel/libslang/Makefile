# $MirOS: ports/devel/libslang/Makefile,v 1.5 2009/03/15 10:10:54 bsiegert Exp $
# $OpenBSD: Makefile,v 1.39 2004/03/04 17:49:26 espie Exp $

COMMENT=	stack-based interpreter for terminal applications

VERSION=	2.1.4
DISTNAME=	slang-${VERSION}
PKGNAME=	libslang-${VERSION}-${DASH_VER}
CATEGORIES=	devel
MASTER_SITES=	ftp://space.mit.edu/pub/davis/slang/v2.1/ \
		http://gd.tuwien.ac.at/editors/davis/slang/v2.1/

HOMEPAGE=	http://www.s-lang.org/
RESPONSIBLE=	Stephen Paskaluk <sap@mirbsd.org>


# Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes

REGRESS_TARGET=		runtests
REGRESS_FLAGS=		TCAPLIB="-ltermlib"

pre-patch:
.for i in aclocal.m4 configure.ac
	mv ${WRKSRC}/autoconf/$i ${WRKSRC}
.endfor

.include <bsd.port.mk>

.if !defined(NO_SHARED_LIBS) || ${NO_SHARED_LIBS:L} == "no"
ALL_TARGET= all elf
INSTALL_TARGET= install-elf
.endif
