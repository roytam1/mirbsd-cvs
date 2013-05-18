# $MirOS: ports/security/gpa/Makefile,v 1.3 2006/09/14 00:12:59 tg Exp $
# $OpenBSD: Makefile,v 1.11 2002/12/29 20:31:40 fgsch Exp $

COMMENT=	graphical interface for GnuPG

VERSION=	0.4.3
DISTNAME=	gpa-${VERSION}
CATEGORIES=    	security x11

HOMEPAGE=	http://www.gnupg.org/gpa.html


PERMIT_PACKAGE_CDROM=	dependency security/gnupg is not allowed for CDROM
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.gnupg.org/gcrypt/alpha/gpa/

BUILD_DEPENDS=	:gnupg-*:security/gnupg
RUN_DEPENDS=	${BUILD_DEPENDS}
LIB_DEPENDS=	gtk.1.2,gdk.1.2::x11/gtk+1

USE_CXX=		Yes # depends on libusb, which uses CXX
USE_X11=		Yes
CONFIGURE_STYLE=	gnu

.include <bsd.port.mk>
