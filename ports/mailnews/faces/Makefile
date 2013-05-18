# $MirOS$
# $OpenBSD: Makefile,v 1.19 2004/01/13 21:23:37 wilfried Exp $

BROKEN=			wants to create /usr/ports/mailnews/faces/w-faces-1.6.1-0/fake-i386/usr/local/share/faces

COMMENT=		visual mail, user and print face server
DISTNAME=		faces-1.6.1
CATEGORIES=		mail

PERMIT_PACKAGE_CDROM=	"no fee"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no fee"
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=	ftp://ftp.cs.indiana.edu/pub/faces/faces/faces-1.6.1/
EXTRACT_SUFX=	.tar.Z

USE_X11=	Yes

WRKDIST=	$(WRKDIR)/faces

post-extract:
	@cd ${WRKSRC} && cp Makefile.dist Makefile

NO_REGRESS=	Yes

.include <bsd.port.mk>
