# $OpenBSD: Makefile,v 1.19 2002/10/25 11:34:24 naddy Exp $

COMMENT=			small & simple FAX send/receive program

DISTNAME=	efax-0.9
PKGNAME=	${DISTNAME}-1
CATEGORIES=	comms


PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_SUNSITE:=apps/serialcomm/fax/}

NO_REGRESS=	Yes

do-install:
	cd ${WRKBUILD}; \
		${INSTALL_PROGRAM} efax efix ${PREFIX}/bin; \
		${INSTALL_SCRIPT} fax ${PREFIX}/bin; \
		${INSTALL_MAN} fax.1 efax.1 efix.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
