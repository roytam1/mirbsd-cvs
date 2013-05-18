# $MirOS: ports/net/ucspi-tcp/Makefile,v 1.5 2008/10/04 19:03:33 tg Exp $

COMMENT=		tools for building TCP client-server applications
CATEGORIES=		net
DISTNAME=		ucspi-tcp-0.88
HOMEPAGE=		http://cr.yp.to/ucspi-tcp.html

# Public Domain: http://cr.yp.to/distributors.html
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://cr.yp.to/ucspi-tcp/

# datasize limit in 'run' files is too low for ld.so
# to be able to pull in libc
LDFLAGS+=		-static

ALL_TARGET=		default
INSTALL_TARGET=		setup check
NO_REGRESS=		Yes

pre-build:
	@print -r -- ${_PASS_CC:T:Q} ${CFLAGS:Q} >${WRKSRC}/conf-cc
	@print -r -- ${_PASS_CC:T:Q} -s ${LDFLAGS:Q} >${WRKSRC}/conf-ld
	@print -r -- ${PREFIX:Q} >${WRKSRC}/conf-home

pre-install:
	@print -r -- ${PREFIX:Q} >${WRKSRC}/conf-home

.include <bsd.port.mk>
