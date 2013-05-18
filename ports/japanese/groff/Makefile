# $MirOS: ports/japanese/groff/Makefile,v 1.2 2005/07/07 21:22:10 bsiegert Exp $
# $OpenBSD: Makefile,v 1.7 2003/06/22 21:18:53 naddy Exp $

COMMENT=			japanese groff
CATEGORIES=	japanese textproc print
PKGNAME=	ja-groff-1.10_0.99-0
DISTNAME=	groff-1.10

PATCHFILES=	jgroff-0.99.diff.gz:0

MASTER_SITES=	${MASTER_SITE_GNU:=groff/}
MASTER_SITES0=	ftp://ftp.ae.keio.ac.jp/pub/GNU/ \
                ftp://ftp.tohoku.ac.jp/pub/GNU/japanese/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_FTP=	Yes

PATCH_DIST_STRIP=	-p1

CONFIGURE_STYLE=	gnu old dest
USE_CXX=		Yes

.include <bsd.port.mk>
