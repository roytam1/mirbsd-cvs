# $MirOS: ports/graphics/mpeg_play/Makefile,v 1.3 2007/04/07 14:32:28 bsiegert Exp $
# $OpenBSD: Makefile,v 1.14 2002/10/27 00:03:16 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=	play mpeg movies on X11

DISTNAME=	mpeg_play-2.4
CATEGORIES=	graphics

MASTER_SITES=	ftp://mm-ftp.cs.berkeley.edu/pub/multimedia/mpeg/play/
EXTRACT_SUFX=	-src.tar.gz

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=	${WRKDIR}/mpeg_play
CONFIGURE_STYLE=	imake
USE_X11=		Yes

pre-patch:
	cp ${WRKSRC}/Imakefile.proto ${WRKSRC}/Imakefile
	cp ${WRKSRC}/mpeg_play.1 ${WRKSRC}/mpeg_play.man

NO_REGRESS=	Yes

post-install:
	${INSTALL_MAN} ${WRKSRC}/mpeg_play.1 ${PREFIX}/man/man1

.include <bsd.port.mk>
