# $MirOS$
# $OpenBSD: Makefile,v 1.6 2004/05/04 11:31:48 naddy Exp $

COMMENT=		graphical representation of CVS repository
DISTNAME=		cvsgraph-1.7.0
CATEGORIES=		devel
HOMEPAGE=		http://www.akhphd.au.dk/~bertho/cvsgraph/

# GNU GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

MASTER_SITES=		${HOMEPAGE}/release/

LIB_DEPENDS+=		gd.18::graphics/gd
MODULES+=		graphics/png

# can possibly go away with gdlib-config and libgd.la on update
LDADD+=			-lttf -ljpeg -lpng -lm -lz

CONFIGURE_STYLE=	autoconf
AUTOCONF_NEW=		Yes
CONFIGURE_ARGS+=	--with-gd=${LOCALBASE:Q}
CONFIGURE_ENV+=		LIBS=${LDADD:Q}

post-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/{doc,examples}/cvsgraph
	${INSTALL_DATA} ${WRKSRC}/cvsgraph.conf \
	    ${PREFIX}/share/examples/cvsgraph/
	${INSTALL_DATA} ${WRKSRC}/README ${PREFIX}/share/doc/cvsgraph/

.include <bsd.port.mk>
