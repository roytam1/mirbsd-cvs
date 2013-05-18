# $MirOS: ports/net/ucspi-tcp/Makefile,v 1.2 2005/07/07 21:25:10 bsiegert Exp $

COMMENT=			tools for building TCP client-server applications
NO_REGRESS=	Yes

CATEGORIES=	net
DISTNAME=	ucspi-tcp-0.88
PKGNAME=	ucspi-tcp-0.88-0

HOMEPAGE=	http://cr.yp.to/ucspi-tcp.html
# I don't maintain this, I just include it for completeness  -tg

# May distribute patches.
# Must not distribute binaries.
# Must not distribute distfiles.
PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	No
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	"http://cr.yp.to/distributors.html"

MASTER_SITES=	http://cr.yp.to/ucspi-tcp/

# datasize limit in 'run' files is too low for ld.so
# to be able to pull in libc
LDFLAGS+=	-static

ALL_TARGET=	default
INSTALL_TARGET=	setup check

pre-build:
	@echo ${CC} ${CFLAGS} > ${WRKSRC}/conf-cc
	@echo ${CC} -s ${LDFLAGS} > ${WRKSRC}/conf-ld
	@echo ${PREFIX} > ${WRKSRC}/conf-home

pre-install:
	@echo ${PREFIX} > ${WRKSRC}/conf-home

.include <bsd.port.mk>
