# $OpenBSD: Makefile,v 1.6 2003/05/24 01:29:15 jolan Exp $

BROKEN=			undefined reference to rexec
COMMENT=			GNU copy-in/out (cpio)

DISTNAME=		cpio-2.5
PKGNAME=		g${DISTNAME}-0
CATEGORIES=		archivers


# GPL/LGPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		${MASTER_SITE_GNU:=cpio/}

CONFIGURE_STYLE=	gnu dest
CONFIGURE_ARGS=		--program-prefix="g"

.include <bsd.port.mk>
