# $MirOS: ports/print/teTeX/base/Makefile,v 1.6 2007/03/01 21:45:53 tg Exp $
# $OpenBSD: Makefile,v 1.25 2003/04/04 21:19:23 sturm Exp $

COMMENT=		TeX distribution, executables
VERSION=		2.0.2
DASH_VER=		2
DISTNAME=		tetex-base-${VERSION}
PKGNAME=		${DISTNAME:S/tetex-/teTeX_/}-${DASH_VER}
CATEGORIES=		print
DISTFILES=		tetex-src-${VERSION}.tar.gz

B_R_DEPENDS+=		:teTeX_texmf->=2.0:print/teTeX/texmf
RUN_DEPENDS+=		:texi2html->=1.56:textproc/texi2html
MODULES+=		graphics/png

CONFIGURE_STYLE=	dest autogen no-autoheader
AUTOGEN=		${SHELL} ${WRKSRC}/reautoconf
USE_CXX=		yes

MODGNU_CONFIG_GUESS_DIRS= \
			${WRKSRC} \
			${WRKSRC}/libs \
			${WRKSRC}/libs/libwww \
			${WRKSRC}/libs/ncurses \
			${WRKSRC}/texk

CONFIGURE_ARGS+=	--disable-multiplatform \
			--without-texinfo \
			--with-system-ncurses \
			--with-system-pnglib \
			--with-pnglib-libdir=${LOCALBASE}/lib \
			--with-pnglib-include=${LOCALBASE}/include/libpng \
			--with-system-zlib

FLAVORS=		no_x11
FLAVOR?=
.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-x
.else
CONFIGURE_ARGS+=	--with-system-t1lib \
			--with-t1lib-libdir=${LOCALBASE}/lib \
			--with-t1lib-include=${LOCALBASE}/include
LIB_DEPENDS+=		t1.4::devel/t1lib
RUN_DEPENDS+=		:ghostscript-*:print/ghostscript/artifex
USE_X11=		Yes
.endif

WRKDIST=		${WRKDIR}/${DISTNAME:S/base/src/}
TETEX_EXDIR=		${PREFIX}/share/examples/teTeX

# find texmf after fake
REGRESS_FLAGS=		DESTDIR=${WRKINST:Q}

pre-patch:
	cd ${WRKSRC}/texk/etc/autoconf; \
	    cp ${LOCALBASE}/share/autoconf-2.13/* .; \
	    chmod u+w *; \
	    patch -l -z .mir.orig <${FILESDIR}/ac.diff

post-configure:
	find ${WRKBUILD} -name Makefile -exec perl -i -pe \
	    's#^(texmf\s*\=\s*)${PREFIX}#$$1\$${${DESTDIRNAME}}${PREFIX}#' {} \;

# need the texmf part visible...
pre-fake:
	${INSTALL_DATA_DIR} ${TEXMF_DIR}
	lndir ${TRUEPREFIX}/share/texmf ${TEXMF_DIR}
	# mktexlsr is too smart for its own good
	rm ${TEXMF_DIR}/ls-R

post-install:
	${INSTALL_DATA_DIR} ${TETEX_EXDIR}
	${INSTALL_DATA} files/tetex.cfg ${TETEX_EXDIR}/tetex.cfg
	${INSTALL_SCRIPT} files/tetex_setup.sh ${PREFIX}/bin/tetex_setup
	perl -i -pe "s#%%SYSCONFDIR%%#${SYSCONFDIR}#;" \
	    -e "s#%%PREFIX%%#${TRUEPREFIX}#;" ${PREFIX}/bin/tetex_setup

# need the texmf part visible...
pre-regress: fake

.include <bsd.port.mk>
