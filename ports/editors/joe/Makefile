# $MirOS: ports/editors/joe/Makefile,v 1.3 2005/09/12 21:35:40 tg Exp $

COMMENT=		"Joe's Own Editor"
CATEGORIES=		editors
DISTNAME=		joe-3.1jupp5
EXTRACT_SUFX=		.cpio.gz
HOMEPAGE=		http://mirbsd.mirsolutions.de/?jupp
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
DOCS=			HINTS INFO LIST NEWS README TODO

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/joe
.for _i in ${DOCS}
	${INSTALL_DATA} ${WRKSRC}/${_i} ${PREFIX}/share/doc/joe/
.endfor

.include <bsd.port.mk>
