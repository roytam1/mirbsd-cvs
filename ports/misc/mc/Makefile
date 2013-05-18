# $MirOS: ports/misc/mc/Makefile,v 1.6 2005/11/17 23:37:13 tg Exp $

COMMENT=		"free Norton Commander clone with many useful features"
DISTNAME=		mc-4.6.1
CATEGORIES=		misc
HOMEPAGE=		http://www.ibiblio.org/mc/
MASTER_SITES=		http://www.ibiblio.org/pub/Linux/utils/file/managers/mc/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# GNU General Public License, Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

FLAVORS=		no_x11
FLAVOR?=

MODULES+=		converters/libiconv
LIB_DEPENDS=		glib.1.2::devel/glib1

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_CONFIG_GUESS_DIRS=${WRKSRC} ${WRKSRC}/vfs/samba
CONFIGURE_ARGS+=	--disable-dependency-tracking \
			--disable-nls \
			--enable-charset \
			--disable-gcc-warnings \
			--with-glib12 \
			--with-libiconv-prefix=${ICONV_PREFIX} \
			--with-mcfs \
			--with-samba \
			--with-configdir=${SYSCONFDIR} \
			--without-ext2undel \
			--without-subshell \
			--with-screen=ncurses \
			--with-edit
CONFIGURE_ENV+=		mc_cv_have_zipinfo=yes

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-x
.else
CONFIGURE_ARGS+=	--with-x
USE_X11=		Yes
.endif

.include <bsd.port.mk>
