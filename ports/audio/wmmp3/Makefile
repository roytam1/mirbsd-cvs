# $OpenBSD: Makefile,v 1.12 2003/12/10 21:28:58 naddy Exp $

COMMENT=			wm-dockapp; front end for mpg123
DISTNAME=		wmmp3-0.12
CATEGORIES=		audio x11 x11/windowmaker
HOMEPAGE=		http://www.dotfiles.com/software/wmmp3/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}

USE_X11=		Yes
NO_REGRESS=		Yes
CONFIGURE_STYLE=	gnu

SAMPLE_DIR=		${PREFIX}/share/examples/wmmp3
SUBST_VARS+=		SAMPLE_DIR

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/wmmp3 ${PREFIX}/bin
	${INSTALL_DATA_DIR} ${SAMPLE_DIR}
	${INSTALL_DATA} ${WRKSRC}/sample.wmmp3 ${SAMPLE_DIR}/dot.wmmp3.sample

.include <bsd.port.mk>
