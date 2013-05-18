# $MirOS$

COMMENT=		displays user-friendly dialog boxes from shell scripts
DISTNAME=		dialog-1.1-20070704
CATEGORIES=		misc
EXTRACT_SUFX=		.tgz
HOMEPAGE=		http://invisible-island.net/dialog/
MASTER_SITES=		ftp://invisible-island.net/dialog/

# GNU LGPLv2.1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES+=		devel/libncursesw
CONFIGURE_STYLE=	autoconf no-autoheader
MODGNU_MIRLIBTOOL=	No
CONFIGURE_ARGS+=	--disable-nls \
			--without-libtool \
			--with-ncursesw \
			--enable-widec
CONFIGURE_ENV+=		am_cv_func_iconv=no	# hidden dep.
MAKE_FILE=		makefile

.include <bsd.port.mk>
