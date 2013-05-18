# $MirOS: ports/editors/joe/Makefile,v 1.11 2007/02/18 23:13:24 tg Exp $

COMMENT=		Joe's Own Editor (including jupp)
CATEGORIES=		editors
DISTNAME=		joe-3.1jupp8
EXTRACT_SUFX=		.cpio.gz
HOMEPAGE=		http://mirbsd.de/jupp
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/jupp/}

# GNU GPL Version 1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/jupp
CONFIGURE_STYLE=	gnu
EXTRA_FAKE_FLAGS=	sysconfdir=${TRUEPREFIX}/share/examples
DOCS=			HINTS INFO LIST NEWS README TODO docs/help-system.html

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/joe
	cd ${WRKSRC} && ${INSTALL_DATA} ${DOCS} ${PREFIX}/share/doc/joe/

.include <bsd.port.mk>
