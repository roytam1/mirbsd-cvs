# $MirOS: ports/voip/iaxcomm/Makefile,v 1.5 2005/08/21 11:50:28 tg Exp $

BROKEN=			severe ressource problems; segfaults if run from wrksrc

COMMENT=			minimal IAX/IAX2 client programme
CATEGORIES=		voip devel net
V=			20050617
DISTNAME=		iaxclient-${V}
EXTRACT_SUFX=		.cpio.gz
PKGNAME=		iaxcomm-${V}-0
HOMEPAGE=		http://iaxclient.sourceforge.net/
RESPONSIBLE=		Thorsten Glaser <tg@66h.42h.de>

# GNU GPL
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MODULES=		x11/wxgtk
LIB_DEPENDS=		iaxclient::voip/iaxclient

WRKDIST=		${WRKDIR}/iaxclient/simpleclient/iaxcomm
MAKE_FILE=		BSDmakefile

post-extract:
	cp ${FILESDIR}/BSDmakefile ${WRKSRC}/

.include <bsd.port.mk>
