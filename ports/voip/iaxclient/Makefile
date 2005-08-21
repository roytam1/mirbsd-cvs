# $MirOS: ports/voip/iaxclient/Makefile,v 1.3 2005/07/07 21:27:29 bsiegert Exp $

COMMENT=		"IAX/IAX2 client library"
CATEGORIES=		voip devel net
DISTNAME=		iaxclient-20050617
EXTRACT_SUFX=		.cpio.gz
PKGNAME=		${DISTNAME}-0
HOMEPAGE=		http://iaxclient.sourceforge.net/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# GNU GPL and LGPL; some BSD
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/iaxclient/lib
MAKE_FILE=		BSDmakefile

post-extract:
	cp ${FILESDIR}/BSDmakefile ${WRKSRC}/

.include <bsd.port.mk>
