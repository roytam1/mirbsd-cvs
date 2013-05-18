#$MirOS: ports/devel/apr/apr/Makefile,v 1.3 2006/12/20 15:31:20 tg Exp $

COMMENT=		Apache portable runtime library
DASH_VER=		0
DISTNAME=		apr-${VERSION}

post-install:
	echo 'H\n/^LDFLAGS/s/=.*/=/\nwq' | ed ${PREFIX}/share/build/apr_rules.mk

.include <bsd.port.mk>
