# $MirOS: ports/editors/joe/Makefile,v 1.21 2011/07/27 19:08:27 tg Exp $

COMMENT=		Joe's Own Editor (including jupp)
CATEGORIES=		editors
DISTNAME=		joe-3.1jupp18
HOMEPAGE=		http://mirbsd.de/jupp
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPL Version 1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

EXTRACT_SUFX=		.cpio.gz
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/jupp/}

WRKDIST=		${WRKDIR}/jupp
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--disable-termidx
EXTRA_FAKE_FLAGS=	sysconfdir=${TRUEPREFIX:Q}/share/examples

post-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/doc/joe
	cd ${WRKSRC:Q} && ${INSTALL_DATA} HINTS INFO LIST NEWS README TODO \
	    docs/help-system.html ${PREFIX:Q}/share/doc/joe/

.include <bsd.port.mk>
