# $MirOS: ports/editors/joe/Makefile,v 1.32 2014/10/23 18:28:57 tg Exp $

COMMENT=		Joe's Own Editor (jupp)
CATEGORIES=		editors
DISTNAME=		joe-3.1jupp29
HOMEPAGE=		http://mirbsd.de/jupp
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>

# GNU GPL Version 1
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

EXTRACT_SUFX=		.tgz
MASTER_SITES=		${_MASTER_SITE_MIRBSD:distfiles/=dist/jupp/}

WRKDIST=		${WRKDIR}/jupp
CONFIGURE_STYLE=	gnu
CONFIGURE_ARGS+=	--disable-termidx
EXTRA_FAKE_FLAGS=	sysconfdir=${TRUEPREFIX:Q}/share/examples

.include <mirports.sys.mk>

.ifdef __CRAZY
CFLAGS+=		-Wno-unused-parameter -Wno-missing-field-initializers \
			-Wno-old-style-definition -Wno-strict-prototypes \
			-Wno-cast-qual \
			-Wno-missing-prototypes -Wno-missing-declarations
.endif

post-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/doc/joe
	cd ${WRKSRC:Q} && ${INSTALL_DATA} HINTS INFO LIST NEWS README \
	    ${PREFIX:Q}/share/doc/joe/

.include <bsd.port.mk>
