# $OpenBSD: Makefile,v 1.10 2002/11/23 07:25:59 pvalchev Exp $

COMMENT=			spreadsheet program under X11

DISTNAME=	xspread3.1.1c
PKGNAME=	xspread-3.1.1c-0
CATEGORIES=	math

# GPLv2
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_OPENBSD}

USE_X11=	Yes
CONFIGURE_STYLE=	gnu old

INSTALL_TARGET= install install.man

post-install:
	@find ${WRKSRC} -name "*.tmp" -delete || :
	${INSTALL_DATA_DIR} \
		${PREFIX}/share/xspread/{doc,documents,tests}
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/xspread
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/xspread
	${INSTALL_DATA} ${WRKSRC}/x/notes ${PREFIX}/share/xspread
	${INSTALL_DATA} ${WRKSRC}/doc/* ${PREFIX}/share/xspread/doc
	${INSTALL_DATA} ${WRKSRC}/documents/* ${PREFIX}/share/xspread/documents
	${INSTALL_DATA} ${WRKSRC}/sample_files/* \
		${PREFIX}/share/examples/xspread
	${INSTALL_DATA} ${WRKSRC}/tests/* ${PREFIX}/share/xspread/tests

.include <bsd.port.mk>
