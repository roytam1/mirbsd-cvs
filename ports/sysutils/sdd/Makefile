# $OpenBSD: Makefile,v 1.14 2003/02/12 15:40:39 naddy Exp $

BROKEN=			this is wrong, we probably want to remove the .if below and use machine-openbsd-mpcc.rul always

COMMENT=		faster and improved version of dd

DISTNAME=	sdd-1.31
CATEGORIES=	sysutils


# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.berlios.de/pub/sdd/

USE_GMAKE=	Yes
MAKE_ENV=	MAKEPROG="${MAKE_PROGRAM}" CCOM=${_PASS_CC:T:Q} COPTX=${CFLAGS:Q}

#.if ${MACHINE} != "i386" || ${_PASS_CC:T:Q} != "cc"
do-configure:
	@ln -sf ${WRKSRC}/RULES/i386-openbsd-cc.rul \
		${WRKSRC}/RULES/${MACHINE}-openbsd-${_PASS_CC:T:Q}.rul
#.endif

NO_REGRESS=	Yes

do-install:
	${INSTALL_PROGRAM} ${WRKBUILD}/sdd/OBJ/${MACHINE}-openbsd-${CC}/sdd \
		${PREFIX}/bin
	${INSTALL_MAN} ${WRKSRC}/sdd/sdd.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
