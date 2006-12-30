# $MirOS$

PKGNAME=vesautils-20060000-0 #XXX
BROKEN=			SVN_DISTF not implemented yet

ONLY_FOR_PLATFORM=	*BSD:*:* Linux:*:*

COMMENT=		VESA video mode utilities
CATEGORIES=		devel multimedia sysutils
SVN_DISTREPO=		svn://svn.mplayerhq.hu/vesautils/trunk
SVN_DISTDATE=		2006/xx/xx
SVN_DISTMODS=		vesautils
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
HOMEPAGE=		http://www.mplayerhq.hu/vesautils/

# GPL?
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

LIB_DEPENDS+=		lrmi::devel/lrmi
NO_REGRESS=		Yes

# TODO: copy BSDmakefile stuff over

.include <bsd.port.mk>
