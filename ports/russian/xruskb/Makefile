# $MirOS: ports/russian/xruskb/Makefile,v 1.3 2007/05/07 22:58:21 tg Exp $
# $OpenBSD: Makefile,v 1.33 2003/08/15 09:56:59 grange Exp $

COMMENT=		english-russian keyboard switcher for X11
DISTNAME=		xruskb-1.15.3
CATEGORIES=		russian x11
MASTER_SITES=		ftp://ftp.yars.free.net/unix/X11/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
CONFIGURE_STYLE=	gnu

FLAVOURS=		motif
FLAVOUR?=

.if ${FLAVOUR:Mopenmotif} || ${FLAVOUR:Mlesstif}
FLAVOUR+=		motif
.endif
.if ${FLAVOUR:L:Mmotif}
USE_MOTIF=		any
CONFIGURE_ARGS=		--with-motif --without-Xaw
.else
CONFIGURE_ARGS=		--without-motif --with-Xaw
.endif

post-patch:
	@perl -i -pe 's!/usr/!${LOCALBASE}/!' \
	    ${WRKSRC}/Xrus.{ad,wmaker}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/xruskb
	${INSTALL_DATA} ${WRKSRC}/xrus.doc-english \
		${PREFIX}/share/doc/xruskb/xrus.doc
	${INSTALL_DATA} ${WRKSRC}/xrus.doc-koi8 ${PREFIX}/share/doc/xruskb
	${INSTALL_DATA} ${WRKSRC}/README* ${PREFIX}/share/doc/xruskb
	${INSTALL_DATA} ${WRKSRC}/Xrus.ad ${PREFIX}/share/xruskb
	${INSTALL_DATA} ${WRKSRC}/Xrus.wmaker ${PREFIX}/share/xruskb

.include <bsd.port.mk>
