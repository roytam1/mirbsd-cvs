# $MirOS: ports/net/xnetload/Makefile,v 1.1.7.1 2005/03/18 15:49:23 tg Exp $

COMMENT=			display usage of a network interface in xload manner

VERSION=		1.11.3
DISTNAME=		xnetload-${VERSION}
CATEGORIES=		net x11

HOMEPAGE=		http://www.xs4all.nl/~rsmith/software/
RESPONSIBLE=		Stephan Eckardt <se@opennerds.org>

# GNU GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

DISTFILES=		xnetload-1.11.3.tar.gz

MASTER_SITES=		http://www.xs4all.nl/~rsmith/software/

USE_X11=		Yes
CONFIGURE_STYLE=	make
NO_REGRESS=		Yes

FILES_LIST=		utils.c utils.h ifstat_netbsd.c

post-patch:
.for file in ${FILES_LIST}
	cp ${FILESDIR}/${file} ${WRKSRC}
.endfor

.include <bsd.port.mk>
