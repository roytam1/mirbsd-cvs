#$MirOS: ports/devel/apr/apr/Makefile,v 1.2 2006/10/11 15:26:40 bsiegert Exp $

COMMENT=		Apache portable runtime library
DASH_VER=		1
DISTNAME=		apr-${VERSION}

post-install:
	echo 'H\n/^LDFLAGS/s/=.*/=/\nwq' | ed ${PREFIX}/share/build/apr_rules.mk

.include <bsd.port.mk>
