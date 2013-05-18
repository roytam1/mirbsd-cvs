# $MirOS: ports/sysutils/bubblemon/Makefile,v 1.3 2006/02/09 11:15:25 tg Exp $
# $OpenBSD: Makefile,v 1.14 2003/09/23 21:18:30 marcm Exp $

COMMENT=			GNOME panel applet that displays the CPU + memory load

DISTNAME=		bubblemon-2.0.1
CATEGORIES=		sysutils x11/gnome

HOMEPAGE=		http://www.d.kth.se/~d92-jwa/code/


MASTER_SITES=		http://savannah.nongnu.org/download/bubblemon/

LIB_DEPENDS=		panel-applet-2::x11/gnome/panel \
			gtop-2.0.0.0,gtop_common-2.0.0.0,gtop_suid_common-2.0.0.0,gtop_sysdeps-2.0.0.0::devel/libgtop

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_X11=		Yes
USE_GMAKE=		Yes
CONFIGURE_STYLE= 	gnu
CONFIGURE_ARGS+= 	${CONFIGURE_SHARED}

.include <bsd.port.mk>
