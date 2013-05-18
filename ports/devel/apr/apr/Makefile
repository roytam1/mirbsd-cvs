#$MirOS: ports/devel/apr/apr/Makefile,v 1.4 2007/12/27 15:33:10 bsiegert Exp $

COMMENT=		Apache portable runtime library
DASH_VER=		0
DISTNAME=		apr-${VERSION}

.include <mirports.sys.mk>

.if ${OStype:L:Mdarwin}
CONFIGURE_ARGS+=	--without-sendfile
.endif

post-install:
	echo 'H\n/^LDFLAGS/s/=.*/=/\nwq' | ed ${PREFIX}/share/build/apr_rules.mk

.include <bsd.port.mk>
