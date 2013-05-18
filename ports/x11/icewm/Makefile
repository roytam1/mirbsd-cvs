# $MirOS: ports/x11/icewm/Makefile,v 1.2 2005/03/27 20:42:17 tg Exp $
# $OpenBSD: Makefile,v 1.16 2004/05/25 16:36:35 naddy Exp $

COMMENT=			small, fast window manager
DISTNAME=		icewm-1.2.20
CATEGORIES=     	x11
HOMEPAGE=		http://www.icewm.org/

# LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=           ${MASTER_SITE_SOURCEFORGE:=icewm/}

LIB_DEPENDS=		Imlib.19::graphics/imlib

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

post-install:
	@perl -pi -e 's:%%SYSCONFDIR%%:${SYSCONFDIR}:g;' \
		-e 's:%%PREFIX%%:${TRUEPREFIX}:g;' \
		${PREFIX}/share/doc/icewm/icewm-7.html
	${INSTALL_DATA} ${FILESDIR}/*.xpm ${PREFIX}/share/icewm/taskbar/

.include <bsd.port.mk>
