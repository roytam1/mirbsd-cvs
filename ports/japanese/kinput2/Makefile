# $MirOS: ports/japanese/kinput2/Makefile,v 1.6 2008/03/09 19:16:01 tg Exp $
# $OpenBSD: Makefile,v 1.14 2003/08/04 13:11:48 espie Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT-canna=			X input method for Japanese, canna support
COMMENT-canna-wnn=		X input method for Japanese, canna and wnn support
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
USE_X11=		Yes
FLAVOURS=		canna wnn
FLAVOUR?=		wnn

.if ${FLAVOUR:L:Mwnn}
BROKEN=			depends on Wnn, which is broken
BUILD_DEPENDS+=		::japanese/Wnn
.endif

.if ${FLAVOUR:L:Mcanna}
LIB_DEPENDS=		canna16::japanese/canna
.endif

PORT_DOCDIR=		${PREFIX}/share/doc/kinput2

pre-configure:
	mv -f ${WRKSRC}/Kinput2.conf ${WRKSRC}/Kinput2.conf.org
	cp ${FILESDIR}/Kinput2.conf ${WRKSRC}/Kinput2.conf
.if ${FLAVOUR:L:Mwnn}
	echo "#define UseWnn" >>${WRKSRC}/Kinput2.conf
.endif
.if ${FLAVOUR:L:Mcanna}
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
