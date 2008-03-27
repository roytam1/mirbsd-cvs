# $MirOS$

COMMENT=		run commands in an environment faking root privileges
CATEGORIES=		sysutils devel
DISTNAME=		fakeroot_1.5.10
PKGNAME=		${DISTNAME:S/_/-/}-${DASH_VER}
HOMEPAGE=		http://packages.debian.org/unstable/utils/fakeroot
MASTER_SITES=		${MASTER_SITE_DEBIAN:=f/fakeroot/}

# GNU GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/${DISTNAME:S/_/-/}

# autogen is required, otherwise configure will loop endlessly
CONFIGURE_STYLE=	autogen
AUTOCONF_NEW=		Yes
AUTOMAKE_VERSION=	1.9

.include <bsd.port.mk>
