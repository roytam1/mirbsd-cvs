# $MirOS: ports/x11/wxgtk/Makefile,v 1.6 2006/02/09 11:15:56 tg Exp $
# $OpenBSD: Makefile,v 1.5 2003/10/08 17:13:18 sturm Exp $

COMMENT=			C++ cross-platform GUI toolkit
DISTNAME=		wxGTK-2.6.1
PKGNAME=		${DISTNAME:L}-0
CATEGORIES=		x11
MASTER_SITES=		${MASTER_SITE_SOURCEFORGE:=wxwindows/}
EXTRACT_SUFX=   	.tar.gz
HOMEPAGE=		http://wxWindows.org/

LIB_DEPENDS+=		gdk.,gtk.::x11/gtk+1 \
			glib.,gmodule.,gthread.::devel/glib1 \
			jpeg.62::graphics/jpeg \
			tiff.35::graphics/tiff \
			expat::textproc/expat
MODULES+=		graphics/png

CONFIGURE_STYLE=	autoconf no-autoheader
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--disable-gtk2 \
			--enable-gui \
			--enable-monolithic \
			${CONFIGURE_SHARED} \
			--enable-optimise \
			--enable-no_deps \
			--enable-compat22 \
			--disable-intl \
			--enable-config \
			--enable-protocols \
			--enable-ftp \
			--enable-http \
			--enable-fileproto \
			--enable-sockets \
			--enable-ipc \
			--enable-apple_ieee \
			--enable-arcstream \
			--enable-catch_segvs \
			--enable-cmdline \
			--enable-datetime \
			--enable-debugreport \
			--enable-dialupman \
			--enable-dynamicloader \
			--enable-exceptions \
			--enable-ffile \
			--enable-file \
			--enable-filesystem \
			--enable-fontmap \
			--enable-fs_inet \
			--enable-fs_zip \
			--enable-geometry \
			--enable-log \
			--enable-longlong \
			--enable-mimetype \
			--enable-snglinst \
			--enable-stdpaths \
			--enable-stopwatch \
			--enable-streams \
			--enable-sysoptions \
			--enable-textbuf \
			--enable-textfile \
			--enable-timer \
			--enable-sound \
			--enable-zipstream \
			--enable-url \
			--enable-protocol \
			--enable-protocol-http \
			--enable-protocol-ftp \
			--enable-protocol-file \
			--enable-threads \
			--enable-docview \
			--enable-help \
			--enable-html \
			--enable-htmlhelp \
			--enable-xrc \
			--enable-printarch \
			--enable-mdi \
			--enable-mdidoc \
			--enable-clipboard \
			--enable-dnd \
			--enable-controls \
			--enable-commondlg \
			--enable-choicedlg \
			--enable-coldlg \
			--enable-filedlg \
			--enable-finddlg \
			--enable-fontdlg \
			--enable-dirdlg \
			--enable-msgdlg \
			--enable-numberdlg \
			--enable-splash \
			--enable-textdlg \
			--disable-tipdlg \
			--enable-progressdlg \
			--enable-wizarddlg \
			--enable-menus \
			--enable-miniframe \
			--enable-tooltips \
			--enable-splines \
			--enable-mousewheel \
			--enable-validators \
			--enable-busyinfo \
			--enable-joystick \
			--enable-dragimage \
			--enable-palette \
			--enable-image \
			--enable-gif \
			--enable-pcx \
			--enable-iff \
			--enable-pnm \
			--enable-xpm \
			--enable-icocur \
			--disable-precomp-headers \
			--with-gtk=2 \
			--with-libpng \
			--with-libjpeg \
			--with-libtiff \
			--with-libxpm \
			--with-opengl \
			--with-regex \
			--with-zlib \
			--with-expat \
			--with-flavour=MirPorts

#USE_GMAKE=		Yes
USE_CXX=		Yes

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

post-install:
	cd ${PREFIX}/lib && for f in lib*.so; do \
		mv $$f $$f.0.0; \
	done
	cd ${PREFIX}/bin; f="$(readlink wx-config)"; \
	    rm wx-config; ln "$f" wx-config

.include <bsd.port.mk>
