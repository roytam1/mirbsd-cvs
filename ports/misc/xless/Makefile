# $MirOS: ports/misc/xless/Makefile,v 1.3 2007/04/18 18:33:30 bsiegert Exp $
# $OpenBSD: Makefile,v 1.15 2002/10/27 21:07:54 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	X11 viewer for text files

DISTNAME=	xless-1.7
CATEGORIES=	misc	

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	${MASTER_SITE_XCONTRIB:=applications/} \
		ftp://ftp.cs.berkeley.edu/ucb/people/dglo/xless/

CONFIGURE_STYLE=imake
USE_X11=	Yes

NO_REGRESS=	Yes

.include <bsd.port.mk>
