# $MirOS: ports/misc/mc/Makefile,v 1.8 2006/02/21 13:39:40 tg Exp $

COMMENT=		"free Norton Commander clone with many useful features"
DISTNAME=		mc-4.6.0
PKGNAME=		${DISTNAME}-5
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

LIB_DEPENDS+=		glib.1.2::devel/glib1
MODULES+=		converters/libiconv

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_CONFIG_GUESS_DIRS=${WRKSRC} ${WRKSRC}/vfs/samba
CONFIGURE_ARGS+=	--disable-dependency-tracking \
			--disable-nls \
			--enable-charset \
			--with-libiconv-prefix=${ICONV_PREFIX} \
			--with-vfs \
			--with-mcfs \
			--with-samba \
			--with-configdir=${SYSCONFDIR} \
			--with-screen=ncurses \
			--with-subshell \
			--with-edit \
			--without-ext2undel
CONFIGURE_ENV+=		mc_cv_have_zipinfo=yes

.if ${FLAVOR:L:Mno_x11}
CONFIGURE_ARGS+=	--without-x
.else
CONFIGURE_ARGS+=	--with-x
USE_X11=		Yes
.endif

.include <bsd.port.mk>
