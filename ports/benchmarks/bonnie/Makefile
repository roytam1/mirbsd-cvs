# $OpenBSD: Makefile,v 1.13 2002/10/24 22:46:16 naddy Exp $

COMMENT=			performance test of filesystem I/O

DISTNAME=	Bonnie
PKGNAME=	bonnie-1.0-0
CATEGORIES=	benchmarks

MASTER_SITES=	ftp://ftp.sunet.se/pub/benchmark/Bonnie/ \
		ftp://swedishchef.lerc.nasa.gov/drlabs/io/
EXTRACT_SUFX=	.tar.Z


# License: BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

NO_REGRESS=	Yes

do-build:
	${_PASS_CC:Q} ${CFLAGS} -o ${WRKBUILD}/bonnie.o -c ${WRKSRC}/Bonnie.c
	cd ${WRKBUILD}; ${_PASS_CC:Q} -static -o bonnie bonnie.o

do-install:
	${INSTALL_PROGRAM_DIR} ${PREFIX}/bin
	${INSTALL_MAN_DIR} ${PREFIX}/man/man1
	${INSTALL_PROGRAM} ${WRKBUILD}/bonnie ${PREFIX}/bin
	${INSTALL_MAN} ${FILESDIR}/bonnie.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
