# $OpenBSD: Makefile,v 1.6 2003/12/05 17:30:22 sturm Exp $

COMMENT=			tool to indent and reformat perl scripts

VSN=		20031021
DISTNAME=	Perl-Tidy-${VSN}
PKGNAME=	perltidy-${VSN}-${DASH_VER}
CATEGORIES=	devel

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=perltidy/}
HOMEPAGE=	http://perltidy.sourceforge.net/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=perl

DOCS=		tutorial.pod testfile.pl stylekey.pod

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/perltidy
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/perltidy
.for f in ${DOCS}
	${INSTALL_DATA} ${WRKSRC}/docs/${f} ${PREFIX}/share/doc/perltidy
.endfor
	${INSTALL_DATA} ${WRKSRC}/examples/* ${PREFIX}/share/examples/perltidy

.include <bsd.port.mk>
