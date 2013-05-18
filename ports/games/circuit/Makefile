# $MirOS: ports/games/circuit/Makefile,v 1.4 2008/10/04 19:03:08 tg Exp $
# $OpenBSD: Makefile,v 1.5 2002/12/16 19:55:15 espie Exp $

COMMENT=			finish-the-cycle logic puzzle
CATEGORIES=	games


DISTNAME=	circuit-0.1.4
MASTER_SITES=	ftp://quatramaran.ens.fr/pub/cigaes/circuit/


# BSD
PERMIT_PACKAGE_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes

LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1

USE_X11=	Yes

do-build:
	cd ${WRKBUILD} && ${_PASS_CC:Q} $(CFLAGS) \
	    $$(gtk-config --cflags --libs) circuit.c -o circuit

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/circuit ${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/circuit.6 ${PREFIX}/man/man6



.include <bsd.port.mk>
