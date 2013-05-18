# $MirOS: ports/essentials/ca-certificates/Makefile,v 1.6 2009/05/17 16:10:05 tg Exp $

COMMENT=		X.509 CA certificate collection
CATEGORIES=		essentials security
MCZ_FETCH=		Yes
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTDATE=		2009/11/15
CVS_DISTMODS=		src/etc/ssl.certs.shar
CVS_DISTFILE=		ca-certificates
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
HOMEPAGE=		http://MirBSD.de/

# copyright law not applicable
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

WRKDIST=		${WRKDIR}/src/etc

do-build:
	cd ${WRKSRC} && \
	    rm -rf build && \
	    mkdir -p build && \
	    cd build && \
	    ${MKSH} ../ssl.certs.shar && \
	    cat * >../pkbundle.pem
	cd ${WRKSRC} && \
	    fgrep '$$Mir''OS:' ssl.certs.shar >-VERSION

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/ca-certificates
	${INSTALL_DATA} ${WRKSRC}/{-VERSION,*.pem,build/*} \
	    ${.CURDIR}/keystore.jks \
	    ${PREFIX}/share/ca-certificates/

.include <bsd.port.mk>
