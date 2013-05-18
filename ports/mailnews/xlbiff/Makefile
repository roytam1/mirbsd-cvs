# $MirOS: ports/mailnews/xlbiff/Makefile,v 1.3 2007/04/12 20:20:04 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2004/05/18 08:45:33 xsa Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	display from/subject from incoming mails using X11

DISTNAME=	xlbiff-3.0
CATEGORIES=	mail x11

MASTER_SITES=	${MASTER_SITE_R5CONTRIB}
EXTRACT_SUFX=	.tar.Z

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

CONFIGURE_STYLE=	imake
USE_X11=		Yes

NO_REGRESS=	Yes

.include <bsd.port.mk>
