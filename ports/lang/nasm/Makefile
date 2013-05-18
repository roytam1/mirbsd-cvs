# $MirOS: ports/lang/nasm/Makefile,v 1.4 2006/02/09 09:36:00 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/04/07 22:54:23 brad Exp $

# XXX why?
ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			general-purpose multi-platform x86 assembler

DISTNAME=	nasm-0.98.38
CATEGORIES=	devel lang

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=nasm/}
HOMEPAGE=	http://nasm.sourceforge.net/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE= gnu

NO_REGRESS=	Yes

FAKE_FLAGS=	INSTALLROOT="${WRKINST}"

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/nasm
	${INSTALL_MAN} ${WRKSRC}/doc/*.doc ${PREFIX}/share/doc/nasm
	${INSTALL_DATA} ${WRKBUILD}/doc/html/*.html ${PREFIX}/share/doc/nasm
	${INSTALL_DATA} ${WRKBUILD}/doc/info/* $(PREFIX)/info

.include <bsd.port.mk>
