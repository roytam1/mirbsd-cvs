# $MirOS: ports/sysutils/xbatt/Makefile,v 1.5 2007/04/16 18:36:50 bsiegert Exp $
# $OpenBSD: Makefile,v 1.10 2002/10/28 19:53:44 naddy Exp $
# $FreeBSD: Makefile,v 1.4 1997/03/10 12:07:35 asami Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	laptop battery status display for X11

DISTNAME=	xbatt-1.2.1
CATEGORIES=	sysutils x11

MASTER_SITES=	http://www.clave.gr.jp/~eto/xbatt/


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	imake noman
USE_X11=		Yes
ONLY_FOR_PLATFORM=	*:*:i386 *:*:macppc

NO_REGRESS=	Yes

.include <bsd.port.mk>
