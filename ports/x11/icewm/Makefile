# $MirOS: ports/x11/icewm/Makefile,v 1.4 2006/10/01 02:13:05 tg Exp $
# $OpenBSD: Makefile,v 1.16 2004/05/25 16:36:35 naddy Exp $

COMMENT=		small, fast window manager with themes
DISTNAME=		icewm-1.2.28
PKGNAME=		${DISTNAME}-1
CATEGORIES=     	x11
HOMEPAGE=		http://www.icewm.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=           ${MASTER_SITE_SOURCEFORGE:=icewm/}

LIB_DEPENDS=		Imlib::graphics/imlib

USE_CXX=		Yes
USE_X11=		Yes
NO_REGRESS=		Yes
CONFIGURE_STYLE= 	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS=		--with-imlib=${PREFIX}/bin \
			--with-docdir=${PREFIX}/share/doc \
			--with-libdir=${PREFIX}/share/icewm \
			--with-cfgdir=${SYSCONFDIR}/icewm \
			--disable-nls \
			--disable-i18n \
			--enable-gradients
INSTALL_TARGET=		install install-man

post-install:
	${INSTALL_DATA} ${FILESDIR}/*.xpm ${PREFIX}/share/icewm/taskbar/
	cd ${PREFIX}/share/icewm/taskbar && \
	    mv start.xpm icewm.xpm && \
	    ln -s bsd-daemon.xpm start.xpm
	for file in share/doc/icewm/icewm-7.html man/man1/icewm.1; do \
		chmod u+w ${PREFIX}/$$file; \
		print '%g#%%SYSCONFDIR%%#s##${SYSCONFDIR}#g\n%g#%%PREFIX%%#s##${TRUEPREFIX}#g\nwq' | \
		    ed -s ${PREFIX}/$$file; \
		chmod ${DOCMODE} ${PREFIX}/$$file; \
	done
	echo 'Theme="metal2/default.theme"' > ${PREFIX}/share/icewm/theme

.include <bsd.port.mk>
