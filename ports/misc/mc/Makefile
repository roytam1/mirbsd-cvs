# $MirOS: ports/misc/mc/Makefile,v 1.27 2010/12/31 17:53:03 tg Exp $

COMMENT=		free Norton Commander clone with many useful features
DISTNAME=		mc-4.6.1
DASH_VER=		18
CATEGORIES=		misc
HOMEPAGE=		http://www.ibiblio.org/mc/
MASTER_SITES=		http://www.ibiblio.org/pub/Linux/utils/file/managers/mc/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# GNU General Public License, Version 2 or later
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS+=		glib.1.2::devel/glib1
MODULES+=		converters/libiconv

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
MODGNU_RECURSE_DIRS=	${WRKSRC}/vfs/samba ${WRKSRC}
CONFIGURE_ARGS+=	--disable-nls \
			--disable-charset \
			--disable-gcc-warnings \
			--with-glib12 \
			--with-libiconv-prefix=${ICONV_PREFIX} \
			--without-x \
			--with-vfs \
			--with-mcfs \
			--with-samba \
			--with-configdir=${SYSCONFDIR} \
			--without-ext2undel \
			--with-subshell \
			--with-screen=mcslang \
			--with-edit
CONFIGURE_ENV+=		ac_cv_path_ZIP=${PREFIX:Q}/bin/zip
CONFIGURE_ENV+=		ac_cv_path_UNZIP=${PREFIX:Q}/bin/unzip
CONFIGURE_ENV+=		mc_cv_have_zipinfo=yes

.include <bsd.port.mk>
