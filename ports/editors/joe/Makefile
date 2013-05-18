# $MirOS: ports/editors/joe/Makefile,v 1.14 2008/05/13 16:47:58 tg Exp $

COMMENT=		Joe's Own Editor (including jupp)
CATEGORIES=		editors
DISTNAME=		joe-3.1jupp10
HOMEPAGE=		http://mirbsd.de/jupp
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# GNU GPL Version 1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

EXTRACT_SUFX=		.cpio.gz
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/jupp/}

WRKDIST=		${WRKDIR}/jupp
CONFIGURE_STYLE=	gnu
EXTRA_FAKE_FLAGS=	sysconfdir=${TRUEPREFIX:Q}/share/examples

post-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/doc/joe
	cd ${WRKSRC:Q} && ${INSTALL_DATA} HINTS INFO LIST NEWS README TODO \
	    docs/help-system.html ${PREFIX:Q}/share/doc/joe/
	cd ${PREFIX:Q}/man/man1 && for i in jmacs jpico jstar jupp rjoe; do \
		ln -s joe.1 $$i.1; \
	done

.include <bsd.port.mk>
