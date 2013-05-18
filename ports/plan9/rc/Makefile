# $MirOS: ports/plan9/rc/Makefile,v 1.6 2008/03/09 17:23:25 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/05/15 03:25:56 markus Exp $

COMMENT=		clone of plan9 shell

VERSION=		1.7.1
DISTNAME=		rc-${VERSION}
DASH_VER=		1
CATEGORIES=		plan9 shells
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>

# web frontend to /n/sources
MASTER_SITES=		http://cm.bell-labs.com/sources/contrib/quanstro/
#			ftp://ftp.sys.toronto.edu/pub/rc/

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVOURS=		static
FLAVOUR?=

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-history --with-editline

.if ${FLAVOUR:L} == "static"
LDSTATIC=		-static
.endif

REGRESS_TARGET= trip

.include <bsd.port.mk>
