# $OpenBSD: Makefile,v 1.23 2003/05/24 01:14:50 jolan Exp $

COMMENT=			block-sorting file compressor, encumbered

DISTNAME=	bzip-0.21
CATEGORIES=	archivers
MASTER_SITES=	${MASTER_SITE_BACKUP}

# GPL + patents
PERMIT_PACKAGE_CDROM=	"patents"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"patents"
PERMIT_DISTFILES_FTP=	Yes

.include <mirports.sys.mk>
COPTS+=			-fomit-frame-pointer -funroll-loops \
			-Wall -Winline -Wshadow -W
EXTRA_MAKE_FLAGS+=	CFLAGS=${CFLAGS:Q}

do-install:
	${INSTALL_PROGRAM} ${WRKSRC}/bzip ${PREFIX}/bin
	@cd ${PREFIX}/bin && ln -fs bzip bunzip
	${INSTALL_MAN} ${WRKSRC}/bzip.1 ${PREFIX}/man/man1
	${INSTALL_MAN} ${WRKSRC}/bzip.1 ${PREFIX}/man/man1/bunzip.1

.include <bsd.port.mk>
