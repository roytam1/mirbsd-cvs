# $OpenBSD: Makefile,v 1.23 2003/06/04 22:16:22 jolan Exp $

COMMENT=			create & extract files from DOS .ARC files

DISTNAME=       arc521e.pl8
PKGNAME=        arc-5.21e-0
CATEGORIES=	archivers
MASTER_SITES=   ftp://ftp.kiarchive.ru/pub/unix/arcers/
EXTRACT_SUFX=   .tar.Z

# Restrictive
PERMIT_PACKAGE_CDROM=	"no modifications"
PERMIT_PACKAGE_FTP=	"no modifications"
PERMIT_DISTFILES_CDROM=	"no fee"
PERMIT_DISTFILES_FTP=	Yes

EXTRA_MAKE_FLAGS=	OPT="${CFLAGS}"

WRKDIST=	${WRKDIR}
NO_REGRESS=	Yes

.include <bsd.port.mk>
