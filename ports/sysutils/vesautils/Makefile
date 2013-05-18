# $MirOS: ports/sysutils/vesautils/Makefile,v 1.2 2008/11/01 22:57:47 tg Exp $

BROKEN=			uses ioperm, iopl, ipv libarch functions

ONLY_FOR_PLATFORM=	*BSD:*:* Linux:*:*

COMMENT=		VESA video mode utilities
CATEGORIES=		devel multimedia sysutils
MCZ_FETCH=		Yes
SVN_DISTFILE=		vesautils
SVN_DISTPATH=		svn://svn.mplayerhq.hu/vesautils/trunk
SVN_DISTREV=		12
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://www.mplayerhq.hu/vesautils/

# GPL?
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS+=		:mirmake->=20081012:devel/mirmake
LIB_DEPENDS+=		lrmi:lrmi->=20061230-1:devel/lrmi
NO_REGRESS=		Yes
MAKE_FILE=		${.CURDIR}/build.mk

.include <bsd.port.mk>
