#$MirOS: ports/devel/apr/apr/Makefile,v 1.1 2006/10/05 21:11:38 bsiegert Exp $

COMMENT=		Apache portable runtime library
DASH_VER=		-1
DISTNAME=		apr-${VERSION}
PKGNAME=		apr-${VERSION}${DASH_VER}

post-install:
	echo 'H\n/^LDFLAGS/s/=.*/=/\nwq' | ed ${PREFIX}/share/build/apr_rules.mk

.include <bsd.port.mk>
