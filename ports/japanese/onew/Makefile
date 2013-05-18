# $MirOS: ports/japanese/onew/Makefile,v 1.5 2008/03/09 17:22:59 tg Exp $
# $OpenBSD: Makefile,v 1.9 2003/08/04 13:11:48 espie Exp $

COMMENT=			library for Japanese Input Method Wnn4

COMMENT-wnn4=			library for Japanese Input Method Wnn4
COMMENT-canna=			library for Japanese Input Method canna
COMMENT-wnn4-canna=		library for Japanese Input Method canna or wnn4
FULLPKGNAME=		ja-onew${FLAVOUR_EXT}-2.2.10-0

DISTNAME=	jvim2.0r+onew2.2.10
CATEGORIES=	japanese

MASTER_SITES=	ftp://ftp.lab.kdd.co.jp/Japan/onew/ \
		ftp://ftp.leo.chubu.ac.jp/pub/editor/jvim/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=wnn4 canna
FLAVOUR?=canna
.if empty(FLAVOUR)
ERRORS+=	"Fatal: You must choose a converter"
.endif

.if ${FLAVOUR:L:Mwnn4}
BROKEN=			depends on Wnn, which is broken
BUILD_DEPENDS=	::japanese/Wnn
USE_X11=	Yes
USE_CXX=	Yes # depends on groff, which uses CXX
.endif

.if ${FLAVOUR:L:Mcanna}
PERMIT_PACKAGE_CDROM=	"Canna prevents it"
LIB_DEPENDS+=	canna.1::japanese/canna
USE_X11=	Yes
.endif

WRKDIST=	${WRKDIR}/onew
ALL_TARGET=	

ONEW_CONF=	${FILESDIR}/ONEW_CONF-for${FLAVOUR_EXT}
LIB_NAME=	libonew${FLAVOUR_EXT}.a
PORT_DOCDIR=	${PREFIX}/share/doc/ja-onew${FLAVOUR_EXT}

post-patch:
	ln -s ${ONEW_CONF} ${WRKSRC}/ONEW_CONF

MAKE_FLAGS=LOCALBASE=${LOCALBASE} CFLAGS='${CFLAGS}'
SUBST_VARS=FLAVOUR_EXT

NO_REGRESS=	Yes

do-install:
	${INSTALL_DATA} ${WRKSRC}/libonew.a ${PREFIX}/lib/${LIB_NAME}
	${INSTALL_DATA_DIR} ${PORT_DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/README.ONEW ${PORT_DOCDIR}

.include <bsd.port.mk>
