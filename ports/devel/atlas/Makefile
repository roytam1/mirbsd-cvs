# $MirOS: ports/devel/atlas/Makefile,v 1.3 2006/02/09 09:35:43 tg Exp $
# $OpenBSD: Makefile,v 1.7 2004/02/25 02:35:15 naddy Exp $

COMMENT=			C++ reference implementation of the Atlas protocol
VERSION=	0.4.3.1
DISTNAME=	Atlas-C++-${VERSION}
PKGNAME=	${DISTNAME:S/C++-//:L}-0
CATEGORIES=	devel

PERMIT_PACKAGE_CDROM=   Yes
PERMIT_PACKAGE_FTP=     Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=   Yes

MASTER_SITES=	ftp://ftp.ecs.soton.ac.uk/pub/worldforge/acorn/0.4/src/ \
		http://kafka.i-site.com/~novalis/mirrors/acorn/0.4/src/

LIB_DEPENDS=	SDL::devel/sdl \
		sigc.0.0:libsigc++-*:devel/libsigc++

USE_X11=	Yes
USE_CXX=	Yes

CONFIGURE_STYLE=autoconf
CONFIGURE_ARGS=	${CONFIGURE_SHARED}

VMEM_WARNING=	Yes

.include <bsd.port.mk>
