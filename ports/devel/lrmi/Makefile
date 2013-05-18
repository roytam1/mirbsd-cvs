# $MirOS: ports/devel/lrmi/Makefile,v 1.3 2008/12/07 18:57:53 tg Exp $

ONLY_FOR_PLATFORM=	*BSD:*:* Linux:*:*

COMMENT=		*nix real mode interface library
CATEGORIES=		devel sysutils
DASH_VER=		1
MCZ_FETCH=		Yes
CVS_DISTREPO=		:pserver:anonymous@lrmi.cvs.sourceforge.net:/cvsroot/lrmi
CVS_DISTDATE=		2006/12/30
CVS_DISTMODS=		lrmi
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://sourceforge.net/projects/lrmi/

# historic permission clause; public domain
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

BUILD_DEPENDS+=		:mirmake->=20090912:devel/mirmake
NO_REGRESS=		Yes
MAKE_FILE=		${.CURDIR}/Makefile.MirPorts
EXTRA_XAKE_FLAGS+=	MAKE_FILE=${MAKE_FILE:Q}

.include <bsd.port.mk>
