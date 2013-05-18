# $MirOS: ports/lang/ocaml/Makefile,v 1.5 2008/10/04 19:03:14 tg Exp $
# $OpenBSD: Makefile,v 1.27 2004/03/05 21:54:35 avsm Exp $

COMMENT=	ML language based on complete class-based objective system
DISTNAME=	ocaml-3.07
PATCHLEVEL=	pl2
PKGNAME=	${DISTNAME}${PATCHLEVEL}-${DASH_VER}
CATEGORIES=	lang
MASTER_SITES=	http://caml.inria.fr/distrib/${DISTNAME}/
DISTFILES=	${DISTNAME}${PATCHLEVEL}.tar.gz ${DOCFILES}
HOMEPAGE=	http://www.ocaml.org/

# QPL/LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	simple
CONFIGURE_ARGS+=-tkdefs '-I${LOCALBASE}/include/tk8.4 -I${LOCALBASE}/include/tcl8.4' 
CONFIGURE_ARGS+=-tklibs -L${LOCALBASE}/lib 
CONFIGURE_ARGS+=-prefix ${PREFIX} 
CONFIGURE_ARGS+=-cc ${_PASS_CC:T:Q}\ ${CFLAGS:Q}
CONFIGURE_ARGS+=-x11include ${X11BASE}/include -x11lib ${X11BASE}/lib

LIB_DEPENDS=	tcl84::lang/tcl/8.4 \
		tk84::x11/tk/8.4

# ocaml's configure script is too smart for its own good
FAKE_FLAGS=	PREFIX=${WRKINST}${PREFIX}

USE_GMAKE=	Yes
USE_X11=	Yes

.if ${MACHINE_ARCH} == "i386" || ${MACHINE_ARCH} == "sparc" || \
	${MACHINE_ARCH} == "alpha" || ${MACHINE_ARCH} == "amd64"
ALL_TARGET=	world bootstrap opt opt.opt
SED_PLIST=	|sed -e '/^%%native%%$$/r${PKGDIR}/PFRAG.native' -e '//d'
.else
ALL_TARGET=	world bootstrap
SED_PLIST=	|sed -e '/^%%native%%$$/d'
.endif

NO_REGRESS=	Yes

DOCFILES=	${DISTNAME}-refman.html.tar.gz

post-extract:
	cp ${PORTSDIR}/infrastructure/db/config.* \
	    ${WRKSRC}/config/gnu/

post-install:
	@${INSTALL_DATA_DIR} ${PREFIX}/share/doc/ocaml/html/libref
	@${INSTALL_DATA} ${WRKDIR}/htmlman/*.{html,gif} \
		${PREFIX}/share/doc/ocaml/html
	@${INSTALL_DATA} ${WRKDIR}/htmlman/libref/* \
		${PREFIX}/share/doc/ocaml/html/libref
	@strip ${PREFIX}/bin/ocamlrun ${PREFIX}/bin/ocamlyacc
	@${INSTALL_DATA} ${WRKSRC}/LICENSE ${PREFIX}/share/doc/ocaml

.include <bsd.port.mk>
