# $MirOS: ports/devel/libncursesw/Makefile,v 1.7 2008/10/15 09:56:21 tg Exp $

COMMENT=			new curses library (wide character version)
COMMENT-data=			terminfo database for ncurses (multifile format)
CATEGORIES=			devel
VSN=				5.5
DISTNAME=			ncurses-${VSN}
PKGNAME=			libncursesw-${VSN}-2
PKGNAME-data=			terminfo-${VSN}-0-wide
HOMEPAGE=			http://www.gnu.org/software/ncurses/ncurses.html
RESPONSIBLE=			Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=			ftp://invisible-island.net/ncurses/ \
				http://ftp.gnu.org/pub/gnu/ncurses/

# X11-style
PERMIT_DISTFILES_CDROM=		Yes
PERMIT_DISTFILES_FTP=		Yes
PERMIT_PACKAGE_CDROM=		Yes
PERMIT_PACKAGE_FTP=		Yes

MULTI_PACKAGES=			-data
SUBPACKAGE?=

NO_REGRESS=			Yes
CONFIGURE_STYLE=		autoconf no-autoheader
CONFIGURE_ARGS+=		--program-transform-name='s,$$,w,' \
				--without-cxx \
				--without-cxx-binding \
				--without-ada \
				--with-libtool \
				${CONFIGURE_SHARED} \
				--enable-static \
				--without-debug \
				--without-profile \
				--enable-rpath \
				--disable-overwrite \
				--with-terminfo-dirs=${PREFIX}/share/terminfo:/usr/share/terminfo \
				--enable-termcap \
				--with-termpath=/usr/share/misc/termcap:/etc/termcap \
				--enable-getcap \
				--disable-root-environ \
				--enable-widec \
				--enable-lp64 \
				--enable-bsdpad \
				--with-rcs-ids \
				--with-manpage-format=normal \
				--with-manpage-renames=${FILESDIR}/man_db.mirports \
				--enable-const \
				--enable-hard-tabs \
				--enable-xmc-glitch \
				--enable-colorfgbg \
				--enable-ext-colors \
				--enable-ext-mouse \
				--enable-echo \
				--enable-warnings
CONFIGURE_ENV+=			ac_cv_sys_long_file_names=yes
EXTRA_XAKE_FLAGS+=		top_builddir=${WRKBUILD} \
				TERM=dumb
INSTALL_TARGET=			install.includes \
				install.libs \
				install.man \
				install.progs \
				install.data

pre-extract:
	@if fgrep "no multibyte characters" /usr/include/machine/limits.h \
	    >/dev/null 2>&1; then \
		print ERROR: your multibyte support is broken; \
		print remove the line with \"no multibyte characters\"; \
		print from /usr/include/machine/limits.h and retry.; \
		exit 1; \
	fi

post-extract:
	cp ${FILESDIR}/read_bsd_terminfo.c ${WRKSRC}/ncurses/tinfo/

.include <bsd.port.mk>
