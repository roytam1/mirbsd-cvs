# $MirOS: ports/plan9/rc/Makefile,v 1.4 2006/09/14 00:12:35 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/05/15 03:25:56 markus Exp $

COMMENT=		clone of plan9 shell

VERSION=		1.7.1
DISTNAME=		rc-${VERSION}
CATEGORIES=		plan9 shells
RESPONSIBLE=		Benny Siegert <bsiegert@gmx.de>
MASTER_SITES=		http://www.star.le.ac.uk/~tjg/rc/release/ \
			ftp://ftp.sys.toronto.edu/pub/rc/
HOMEPAGE=		http://www.star.le.ac.uk/~tjg/rc/

# BSD-like
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

FLAVORS=		static
FLAVOR?=

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-history --with-editline

.if ${FLAVOR:L} == "static"
LDSTATIC=		-static
.endif

REGRESS_TARGET= trip

.include <bsd.port.mk>
