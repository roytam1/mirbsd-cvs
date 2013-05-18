# $MirOS: ports/editors/joe/Makefile,v 1.12 2007/02/22 22:57:50 tg Exp $

COMMENT=		Joe's Own Editor (including jupp)
CATEGORIES=		editors
DISTNAME=		joe-3.1jupp8
DASH_VER=		1
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

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/joe
	cd ${WRKSRC} && ${INSTALL_DATA} HINTS INFO LIST NEWS README TODO \
	    docs/help-system.html ${PREFIX}/share/doc/joe/
	cd ${PREFIX}/man/man1 && for i in jmacs jpico jstar jupp rjoe; do \
		ln -s joe.1 $$i.1; \
	done

.include <bsd.port.mk>
