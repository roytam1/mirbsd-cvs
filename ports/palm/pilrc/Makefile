# $MirOS: ports/palm/pilrc/Makefile,v 1.4 2006/09/14 00:12:33 tg Exp $
# $OpenBSD: Makefile,v 1.7 2002/12/29 20:31:39 fgsch Exp $

COMMENT=			generate resources for PalmOS applications from text descr

DISTNAME=	pilrc-2.8p5
PKGNAME=	${DISTNAME:S/p5/.5/}-0
CATEGORIES=	palm devel

HOMEPAGE=	http://www.ardiri.com/index.php?redir=palm\&cat=pilrc


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://www.hig.se/~ardiri/download/palm/

FLAVOURS=	no_x11
FLAVOUR?=

USE_GMAKE=	Yes
NO_REGRESS=	Yes
CONFIGURE_STYLE= gnu

.if ${FLAVOUR:L:Mno_x11}
CONFIGURE_ARGS=	--disable-pilrcui
.else
USE_X11=	Yes
LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1
CONFIGURE_ARGS= --enable-pilrcui
.endif

DOCDIR=		${PREFIX}/share/doc/pilrc

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR} ${DOCDIR}/images
	cd ${WRKSRC}/doc && \
		${INSTALL_DATA} archive.html download.html index.html \
		contrib.html history.html manual.html ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/images/download.gif ${DOCDIR}/images

.include <bsd.port.mk>
