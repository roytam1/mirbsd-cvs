# $MirOS$
# $OpenBSD: Makefile,v 1.5 2004/05/25 08:03:54 xsa Exp $

COMMENT=		RSS Aggregator Without Delusions Of Grandeur
DISTNAME=		rawdog-1.12
CATEGORIES=		www news
HOMEPAGE=		http://offog.org/code/rawdog.html

# GPL
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM= Yes
PERMIT_DISTFILES_FTP=	Yes

MASTER_SITES=		http://offog.org/files/

MODULES+=		lang/python
MODULES+=		textproc/expat

RUN_DEPENDS+=		${MODPY_EXPAT_DEPENDS}

NO_REGRESS=		Yes

DOCDIR=			${PREFIX}/share/doc/rawdog
EXAMPLESDIR=		${PREFIX}/share/examples/rawdog

do-configure:
	@perl -pi -e \
		's,/usr/bin/env python,/usr/bin/env python${MODPY_VERSION},g' \
		${WRKSRC}/rawdog

post-install:
	${INSTALL_DATA_DIR} ${DOCDIR}
	${INSTALL_DATA} ${WRKSRC}/README ${DOCDIR}/
	${INSTALL_DATA_DIR} ${EXAMPLESDIR}
	${INSTALL_DATA} ${WRKSRC}/config ${EXAMPLESDIR}/
	${INSTALL_DATA} ${WRKSRC}/style.css ${EXAMPLESDIR}/

.include <bsd.port.mk>
