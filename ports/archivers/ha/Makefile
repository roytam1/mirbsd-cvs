# $OpenBSD: Makefile,v 1.21 2003/05/24 01:40:38 jolan Exp $

COMMENT=			archive files using the HSC compression method

DISTNAME=	ha0999
PKGNAME=	ha-0.999b-0
CATEGORIES=	archivers
MASTER_SITES=	ftp://ftp.kiarchive.ru/pub/unix/arcers/
EXTRACT_SUFX=	.tgz

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

USE_GMAKE=	Yes

CFLAGS+=	-Wall -c -I../$$(MCH) -I../include

MAKE_FILE=	makefile.nix

WRKDIST=	${WRKDIR}

ALL_TARGET=	ha

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/ha ${PREFIX}/bin

NO_REGRESS=	Yes

.include <bsd.port.mk>
