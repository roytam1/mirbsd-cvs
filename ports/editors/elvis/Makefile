# $OpenBSD: Makefile,v 1.8 2003/04/08 13:28:59 naddy Exp $

COMMENT=			clone of the ex/vi text editor

DISTNAME=	elvis-2.1_4
PKGNAME=	${DISTNAME:S/_/./}-0
CATEGORIES=	editors
HOMEPAGE=	http://www.fh-wedel.de/elvis/

# Artistic
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.cs.pdx.edu/pub/elvis/ \
		ftp://ftp.fh-wedel.de/pub/elvis/

FLAVOURS=	no_x11
FLAVOUR?=

CONFIGURE_STYLE= simple
CONFIGURE_ARGS=	--bindir=${PREFIX}/bin --datadir=${PREFIX}/share/elvis
.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS+= --with-x=no
.else
CONFIGURE_ARGS+= --with-x --x-includes=${X11BASE}/include \
		 --x-libraries=${X11BASE}/lib
USE_X11=	Yes
.endif

NO_REGRESS=	Yes

do-install:
.for prog in elvis elvtags ref
	${INSTALL_PROGRAM} ${WRKSRC}/${prog} ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/lib/${prog}.man ${PREFIX}/man/man1/${prog}.1
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/elvis
	${INSTALL_DATA} ${WRKSRC}/lib/* ${PREFIX}/share/elvis

.include <bsd.port.mk>
