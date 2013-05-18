# $MirOS: ports/editors/vim/stable/Makefile,v 1.16 2008/03/09 17:22:37 tg Exp $
# $OpenBSD: Makefile,v 1.93 2004/06/09 18:43:16 lebel Exp $

COMMENT=		vi clone, many additional features
COMMENT-lang=		vi clone, NLS subpackage

DISTNAME=		vim-7.1
REVISION=		266
VERSION=		7.1.${REVISION}
PKGNAME=		vim-${VERSION}-${DASH_VER}
P=			${DISTNAME:C/[-\.]//g}
CATEGORIES=		editors
MASTER_SITES=		ftp://ftp.vim.org/pub/vim/unix/ \
			ftp://ftp.home.vim.org/pub/vim/unix/ \
			ftp://ftp.berlin.de.vim.org/unix/
MASTER_SITES0=		${MASTER_SITES:S/unix/patches\/7.1/}
MASTER_SITES1=		${MASTER_SITES:S/unix/extra/}
DISTFILES=		${DISTNAME}.tar.bz2 \
			${DISTNAME}-extra.tar.gz:1 \
			${DISTNAME}-lang.tar.gz:1
DIST_SUBDIR=		vim7
HOMEPAGE=		http://www.vim.org/

PATCHFILES=		7.1.001-100.gz:0
PATCHFILES+=		7.1.101-200.gz:0

# WTF?
_patches!=		jot -w%03d - 201 ${REVISION} 1
.for p in ${_patches}
PATCHFILES+=		7.1.${p}:0
.endfor

# allow vim to build on m68k and vax
.if (${MACHINE_ARCH} == "m68k")
PATCH_LIST=		patch-* sup-m68k-*
.elif (${MACHINE_ARCH} == "vax")
PATCH_LIST=		patch-* sup-vax-*
.endif

# donation-ware
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		devel/gettext

MULTI_PACKAGES=		-lang
SUBPACKAGE?=
.if defined(PACKAGING) && ${SUBPACKAGE} == "-lang"
.  for i in ${FLAVOUR:L}
_flavour:=${_flavour},$i
.  endfor
RUN_DEPENDS=		::editors/vim/stable${_flavour}
PKG_ARCH=		*
.endif

.for i in ${MULTI_PACKAGES}
PKGNAME$i=		vim$i-${VERSION}-${DASH_VER}
.endfor

FLAVOURS=		huge gtk gtk2 athena motif no_x11 perl python ruby
FLAVOUR?=		gtk

CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--with-tlib="curses" --enable-multibyte

.if ${FLAVOUR:Mopenmotif} || ${FLAVOUR:Mlesstif}
FLAVOUR+=		motif
.endif

.if ${FLAVOUR:L:Mhuge}
CONFIGURE_ARGS+=	--with-features=huge
.endif

.if ${FLAVOUR:L:Mperl}
CONFIGURE_ARGS+=	--enable-perlinterp
.endif

.if ${FLAVOUR:L:Mpython}
PYTHON_VER=		2.3
CONFIGURE_ENV+=		vi_cv_path_python=${LOCALBASE:Q}/bin/python${PYTHON_VER}
CONFIGURE_ARGS+=	--enable-pythoninterp \
			--with-python-config-dir=${LOCALBASE:Q}/lib/python${PYTHON_VER}/config
LIB_DEPENDS+=		python${PYTHON_VER}.0.0:python-${PYTHON_VER}*:lang/python/${PYTHON_VER}
.endif

.if ${FLAVOUR:L:Mruby}
CONFIGURE_ARGS+=	--enable-rubyinterp
MAKE_ENV+=		RUBY=${LOCALBASE:Q}/bin/ruby
LIB_DEPENDS+=		ruby::lang/ruby
.endif

.if ${FLAVOUR:L:Mno_x11} && \
    !${FLAVOUR:L:Mgtk} && !${FLAVOUR:L:Mmotif} && !${FLAVOUR:L:Mathena} && \
    !${FLAVOUR:L:Mgtk2}
CONFIGURE_ARGS+=	--disable-gui \
			--without-x
.elif ${FLAVOUR:L:Mmotif} && \
    !${FLAVOUR:L:Mgtk} && !${FLAVOUR:L:Mno_x11} && !${FLAVOUR:L:Mathena} && \
    !${FLAVOUR:L:Mgtk2}
USE_X11=		Yes
CONFIGURE_ARGS+=	--enable-gui=motif \
			--with-x \
			--enable-fontset \
			--enable-xim
CONFIGURE_ENV+=		MOTIFHOME=${X11BASE:Q}
USE_MOTIF=		any
.elif ${FLAVOUR:L:Mathena} && \
    !${FLAVOUR:L:Mgtk} && !${FLAVOUR:L:Mno_x11} && !${FLAVOUR:L:Mmotif} && \
    !${FLAVOUR:L:Mgtk2}
USE_X11=		Yes
CONFIGURE_ARGS+=	--enable-gui=athena \
			--with-x \
			--enable-fontset \
			--enable-xim
.elif ${FLAVOUR:L:Mgtk} && \
    !${FLAVOUR:L:Mmotif} && !${FLAVOUR:L:Mno_x11} && !${FLAVOUR:L:Mathena} && \
    !${FLAVOUR:L:Mgtk2}
USE_X11=		Yes
LIB_DEPENDS+=		gtk.1.2,gdk.1.2::x11/gtk+1
CONFIGURE_ARGS+=	--enable-gui=gtk \
			--with-x \
			--enable-fontset \
			--enable-xim \
			--disable-gtk2-check
.elif ${FLAVOUR:L:Mgtk2} && \
    !${FLAVOUR:L:Mmotif} && !${FLAVOUR:L:Mno_x11} && !${FLAVOUR:L:Mathena} && \
    !${FLAVOUR:L:Mgtk}
USE_X11=		Yes
MODULES+=		devel/pkgconfig
LIB_DEPENDS+=		gdk-x11-2.0.0.11,gdk_pixbuf-2.0.0.11,gtk-x11-2.0.0.11::x11/gtk+
CONFIGURE_ARGS+=	--enable-gui=gtk2 \
			--with-x \
			--enable-fontset \
			--enable-xim \
			--disable-gtk-check \
			--enable-gtk2-check
.else
ERRORS+=		"Fatal: You must select one GUI interface: no_x11, gtk, athena or motif"
.endif

WRKDIST=		${WRKDIR}/${P}
WRKSRC=			${WRKDIST}/src

SUBST_VARS=		P

.include <mirports.sys.mk>

# don't try to regenerate the configure script. Works around the fact that
# auto/configure.in is newer than auto/configure.
post-patch:
	touch ${WRKBUILD}/auto/configure

post-configure:
	touch ${WRKBUILD}/auto/config.mk

pre-build:
	cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} \
	    ${MAKE_PROGRAM} ${MAKE_FLAGS} xxd/xxd

post-install:
	${INSTALL_DATA} ${FILESDIR}/pf.vim ${PREFIX}/share/vim/${P}/syntax

.include <bsd.port.mk>
