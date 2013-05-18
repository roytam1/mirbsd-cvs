# $MirOS: ports/japanese/kinput2/Makefile,v 1.2 2005/07/07 21:22:14 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2003/08/04 13:11:48 espie Exp $

COMMENT-canna=			X input method for Japanese, canna support
COMMENT-canna-wnn=			X input method for Japanese, canna and wnn support
COMMENT-wnn=			X input method for Japanese, wnn support

DISTNAME=		kinput2-v3.1
PKGNAME=		ja-kinput2-3.1-0
MASTER_SITES=		ftp://ftp.sra.co.jp/pub/x11/kinput2/
CATEGORIES=		japanese x11

# badly worded BSD-style
PERMIT_PACKAGE_CDROM=	"without fee"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"without fee"
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	imake
FLAVORS=		canna wnn
FLAVOR?=		wnn

.if ${FLAVOR:L:Mwnn}
BUILD_DEPENDS+=		::japanese/Wnn
.endif

.if ${FLAVOR:L:Mcanna}
LIB_DEPENDS=		canna16::japanese/canna
.endif

PORT_DOCDIR=		${PREFIX}/share/doc/kinput2

pre-configure:
	mv -f ${WRKSRC}/Kinput2.conf ${WRKSRC}/Kinput2.conf.org
	cp ${FILESDIR}/Kinput2.conf ${WRKSRC}/Kinput2.conf
.if ${FLAVOR:L:Mwnn}
	echo "#define UseWnn" >>${WRKSRC}/Kinput2.conf
.endif
.if ${FLAVOR:L:Mcanna}
	echo "#define UseCanna" >>${WRKSRC}/Kinput2.conf
.endif

NO_REGRESS=	Yes

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/kinput2
	cp ${WRKSRC}/README ${PORT_DOCDIR}
	cp ${WRKSRC}/NEWS ${PORT_DOCDIR}
	@(cd ${WRKSRC}/doc; tar -cf - . | \
		(cd ${PORT_DOCDIR}; tar -xf -))
	@chown -R ${SHAREOWN}:${SHAREGRP} ${PORT_DOCDIR}

.include <bsd.port.mk>
