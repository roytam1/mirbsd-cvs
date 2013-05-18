# $OpenBSD: Makefile,v 1.13 2003/11/13 01:18:45 pvalchev Exp $
# losely based on the FreeBSD port

BROKEN=		Hangs at runtime during build process

COMMENT=			scheme r5 interpreter

CATEGORIES=	lang

V=5d3
DISTNAME=	scm$V
PKGNAME=	scm-$V-0
EXTRACT_SUFX=	.zip

HOMEPAGE=	http://swissnet.ai.mit.edu/~jaffer/SCM.html

MASTER_SITES=	ftp://ftp.swiss.ai.mit.edu/pub/scm/


WRKDIST=	${WRKDIR}/scm

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_FTP=	Yes

SCM_DATA=	COPYING Iedline.scm Init5d3.scm Link.scm \
		Macexp.scm Macro.scm Transcen.scm Tscript.scm mkimpcat.scm \
		disarm.scm build.scm split.scm

FEATURES=arrays bignums cautious edit-line curses posix socket unix \
dynamic-linking i/o-extensions inexact regex

FLAVOURS=no_x11

FLAVOUR?=
.if ${FLAVOUR:L:Mno_x11}
.else
FEATURES+=	x
OPTIONS+=	--compiler-options=-I${X11BASE}/include
OPTIONS+=	--linker-options=-L${X11BASE}/lib
SCM_DATA+=	x11.scm xevent.scm
USE_X11=	Yes
.endif

BUILD_DEPENDS=::devel/slib
RUN_DEPENDS=::devel/slib

post-build:
	cd ${WRKSRC} && ${MAKE_ENV} PATH=${WRKSRC}:${PORTPATH} /bin/sh ./build \
	    -F '${FEATURES}' \
	    ${OPTIONS} \
	    -h system \
	    -o scm \
	    -s "${PREFIX}/share/scm/"
	cd ${WRKSRC} && ${MAKE_ENV} PATH=${WRKSRC}:${PORTPATH} /bin/sh ./build \
	    -F '${FEATURES} sicp' \
	    ${OPTIONS} \
	    -h system \
	    -o scm-sicp \
	    -s "${PREFIX}/share/scm/"

ALL_TARGET=	scmlit

#CFLAGS+=	-Dunix
MAKE_FLAGS=	LD=${_PASS_CC:T:Q}
MAKE_ENV=	SCHEME_LIBRARY_PATH=${LOCALBASE}/share/slib/

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/scm	${PREFIX}/bin
	${INSTALL_PROGRAM} ${WRKBUILD}/scm-sicp	${PREFIX}/bin
	${INSTALL_MAN} ${WRKBUILD}/scm.1	${PREFIX}/man/man1
	${INSTALL_DATA_DIR} ${PREFIX}/share/scm
	${INSTALL_DATA_DIR} ${PREFIX}/include/scm
	${INSTALL_DATA} ${WRKBUILD}/scm{,flags,fig}.h ${PREFIX}/include/scm
	sed -e 's,@PREFIX@,${TRUEPREFIX},' \
	    <${FILESDIR}/require.scm.in \
	    >${PREFIX}/share/scm/require.scm
.for file in ${SCM_DATA}
	${INSTALL_DATA} ${WRKSRC}/${file} ${PREFIX}/share/scm
.endfor
	${INSTALL_DATA} ${WRKSRC}/scm.info ${PREFIX}/info
.if ${FLAVOUR:L:Mno_x11}
.else
	${INSTALL_DATA} ${WRKSRC}/Xlibscm.info ${PREFIX}/info
.endif

REGRESS_TARGET=	check

.include <bsd.port.mk>
