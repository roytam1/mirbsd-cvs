# $MirOS: ports/editors/xemacs21/Makefile,v 1.7 2006/12/20 15:31:23 tg Exp $
# $OpenBSD: Makefile,v 1.20 2003/07/06 18:34:48 naddy Exp $

COMMENT=		heavily customizable and extensible editor

VERSION=		21.4.12
DASH_VER=		1
DISTNAME=		xemacs-${VERSION}
CATEGORIES=     	editors

HOMEPAGE=		http://www.xemacs.org/

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

# where the source files and patches can be fetched
MASTER_SITES= 	ftp://ftp.xemacs.org/pub/xemacs/xemacs-21.4/ \
		ftp://ftp.oleane.net/pub/xemacs/xemacs-21.4/ \
		ftp://ftp.pasteur.fr/pub/computing/xemacs/xemacs-21.4/ \
		ftp://ftp.mpi-sb.mpg.de/pub/gnu/mirror/ftp.xemacs.org/xemacs/xemacs-21.4/ \
		ftp://ftp.usyd.edu.au/pub/Xemacs/xemacs-21.4/ \
		ftp://ftp.lab.kdd.co.jp/xemacs/xemacs-21.4/ \
		ftp://ftp.th-darmstadt.de/pub/editors/xemacs/xemacs-21.4/ \
      		ftp://ftp.funet.fi/pub/mirrors/ftp.xemacs.org/pub/tux/xemacs/xemacs-21.4/

# Dependencies are very flavours-specific, you have
# to select a flavour set to know them

# build/configuration variables

# this one is not "toggle-able" in the configure script
MODULES=	devel/gettext

#USE_GMAKE=		Yes

# 'configure.in' modified to generate a 'configure'
# that knows about curses really being ncurses

CONFIGURE_STYLE=	old gnu autoconf dest
CONFIGURE_ARGS+=	--infodir='$${DESTDIR}${PREFIX}/info/${DISTNAME}' \
			--infopath='${LOCALBASE}/info/${DISTNAME}:${LOCALBASE}/info:usr/share/info' \
			--site-prefixes='${LOCALBASE}:/usr' \
			--without-ldap \
			--without-postgresql \
			--without-cde \
			--without-offix \
			--without-dragndrop \
			--without-gpm \
			--with-msw=no \
			--without-tooltalk \
			--with-sound=no \
			--with-xface=no \
			--without-wnn6 \
			--without-gtk \
			--without-gnome \
			--with-database=berkdb \
			--with-file-coding=yes \
			--with-system-malloc \
			--pdump

# there is not (yet) bsd sound support in XEmacs
# XEmacs does not work with OpenLDAP (linking problem, 
# will try to fix if somebody asks)

FAKE_FLAGS=	prefix='$${WRKINST}$${DESTDIR}${PREFIX}' \
		infodir='$${WRKINST}$${DESTDIR}${PREFIX}/info/${DISTNAME}'

####

# Arch string for configure
GCCARCH=        ${OStriplet}

CONFIGURE_ARGS+=	${GCCARCH}
SUBST_VARS=	GCCARCH

#### Flavours

# generic flavours
FLAVOURS=	mule canna wnn

# X11 Related
FLAVOURS+=	no_x11

FLAVOUR?=

#
# X11-related
#

.if ${FLAVOUR:L:Mno_x11}

CONFIGURE_ARGS+=--without-x11

.else

### X11-dependent flavours
USE_X11=	Yes

CONFIGURE_ARGS+=	--with-menubars=lucid

CONFIGURE_ARGS+=--with-scrollbars=lucid \
		--with-dialogs=athena \
		--with-widgets=athena

LIB_DEPENDS+=	jpeg.62::graphics/jpeg
CONFIGURE_ARGS+=--with-jpeg
MODULES+=		graphics/png
CONFIGURE_ARGS+=--with-png \
		--site-includes="${LOCALBASE}/include/libpng"

LIB_DEPENDS+=	tiff.35::graphics/tiff
CONFIGURE_ARGS+=--with-tiff

. if ${FLAVOUR:L:Mmule}
CONFIGURE_ARGS+=	--with-xim=xlib
# prevents XEmacs from using motif's XIM which coredumps a lot
. endif

### end of X11 dependant flavours
.endif

#
# MULE (MUlti Lingual Emacs) RELATED 
# I18N
#

.if ${FLAVOUR:L:Mmule}
CONFIGURE_ARGS+=--with-mule

. if ${FLAVOUR:L:Mcanna}
LIB_DEPENDS+=	canna16::japanese/canna
CONFIGURE_ARGS+=--with-canna
. else
CONFIGURE_ARGS+=--with-canna=no
. endif

. if ${FLAVOUR:L:Mwnn}
BUILD_DEPENDS+= ::japanese/Wnn
CONFIGURE_ARGS+=--with-wnn
. else
CONFIGURE_ARGS+=--with-wnn=no
. endif

.else

. if ${FLAVOUR:L:Mcanna} || ${FLAVOUR:L:Mwnn}
ERRORS+= "Fatal: You cannot use MULE-dependant flavours without MULE support"
. endif

CONFIGURE_ARGS+=--with-mule=no \
		--with-canna=no \
		--with-wnn=no
.endif

#######
STRIP_EXECS=    cvtmail digest-doc fakemail gnuserv hexl make-docfile \
		mmencode movemail profile sorted-doc wakeup yow
STRIP_PROGS=	${DISTNAME} gnuclient xemacs-b2m xemacs-ctags \
		xemacs-etags ootags

post-install:
# Stripping
.for file in ${STRIP_PROGS}
	@strip ${PREFIX}/bin/${file}
.endfor
.for file in ${STRIP_EXECS}
	@strip ${PREFIX}/lib/${DISTNAME}/${GCCARCH}/${file}
.endfor
.if !defined(LOCKDIR)
	@rm -rf ${PREFIX}/lib/xemacs
.endif

.include <bsd.port.mk>
