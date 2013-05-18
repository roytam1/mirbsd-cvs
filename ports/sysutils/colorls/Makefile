# $MirOS: ports/sysutils/colorls/Makefile,v 1.4 2008/06/08 16:19:07 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2007/08/11 18:41:28 naddy Exp $

BROKEN=		unfetchable distfile; maybe convert to CVS_DIST* from obsd or mbsd?

COMMENT=	ls that can use color to display file attributes

DISTNAME=	ls-4.2
PKGNAME=	color${DISTNAME}-${DASH_VER}
CATEGORIES=	sysutils

# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	http://sites.inka.de/~mips/unix/distfiles/

WRKDIST=	${WRKDIR}/ls
NO_REGRESS=	Yes

# copy file and substitute a string near a CVS keyword
pre-patch:
	sed 's/^\.Dt LS/.Dt COLORLS/' ${WRKSRC}/ls.1 >${WRKSRC}/colorls.1

.include <bsd.port.mk>
