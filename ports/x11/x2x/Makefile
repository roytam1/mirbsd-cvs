# $OpenBSD: Makefile,v 1.10 2002/10/29 19:48:59 naddy Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:* OpenBSD:*:*

COMMENT=			one keyboard/mouse to multiple X displays
DISTNAME=		x2x-1.27
CATEGORIES=     	x11


# BSD
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://gatekeeper.dec.com/pub/DEC/SRC/x2x/ \
		ftp://ftp.digital.de/Digital/SRC/x2x/ \
		ftp://ftp.europe.digital.com/pub/DEC/SRC/x2x/

USE_X11=	Yes
CONFIGURE_STYLE=	imake

pre-build:
	@nroff -man ${WRKSRC}/x2x.1 > ${WRKSRC}/x2x.man 2> /dev/null

NO_REGRESS=	Yes

.include <bsd.port.mk>
