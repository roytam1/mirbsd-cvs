# $OpenBSD: Makefile,v 1.20 2003/06/17 00:27:46 avsm Exp $

COMMENT=			biff-type program, designed to match AfterStep

DISTNAME=	asmail-0.56
PKGNAME=	asmail-0.56-1
CATEGORIES=	mail

MASTER_SITES=	${MASTER_SITE_SOURCEFORGE:=asmail/} \
		ftp://gates.enemy.at/pub/

HOMEPAGE=	http://asmail.sourceforge.net/

LIB_DEPENDS=	jpeg.62::graphics/jpeg

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=	Yes

CONFIGURE_STYLE= gnu
CONFIGURE_ARGS=	--enable-shaping

post-patch:
	@sed -e s#!!PREFIX!!#${PREFIX}#g \
	 ${WRKSRC}/sample.asmailrc > ${WRKSRC}/sample.asmailrc.new
	@mv ${WRKSRC}/sample.asmailrc.new ${WRKSRC}/sample.asmailrc

NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/include/X11/pixmaps/cloud-e
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/asmail
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/asmail
	${INSTALL_MAN} ${WRKSRC}/asmail.man ${PREFIX}/man/cat1/asmail.0
	${INSTALL_DATA} ${WRKSRC}/pixmaps/cloud-e/*.xpm ${PREFIX}/include/X11/pixmaps/cloud-e
	${INSTALL_DATA} ${WRKSRC}/pixmaps/*.xpm ${PREFIX}/include/X11/pixmaps
	${INSTALL_DATA} ${WRKSRC}/sample.asmailrc ${PREFIX}/share/examples/asmail
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/asmail

.include <bsd.port.mk>
