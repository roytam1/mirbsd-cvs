# $MirOS: ports/essentials/ca-certificates/Makefile,v 1.11 2011/09/03 16:39:09 tg Exp $

COMMENT=		X.509v3 Root CA bundle (collection of CA certificates)
CATEGORIES=		essentials security
MCZ_FETCH=		Yes
CVS_DISTREPO=		${_MIROS_ANONCVS}
CVS_DISTDATE=		2012/05/30 18:00
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
	cd ${WRKSRC:Q} && \
	    rm -rf build && \
	    mkdir -p build && \
	    cd build && \
	    ${MKSH} ../ssl.certs.shar && \
	    cat * >../pkbundle.pem
	cd ${WRKSRC:Q} && \
	    fgrep '$$Mir''OS:' ssl.certs.shar >-VERSION

do-install:
	${INSTALL_DATA_DIR} ${PREFIX:Q}/share/ca-certificates
	${INSTALL_DATA} ${WRKSRC:Q}/{-VERSION,*.pem,build/*} \
	    ${.CURDIR:Q}/keystore.{gcj,jks} \
	    ${PREFIX:Q}/share/ca-certificates/
	cd ${PREFIX}/share/ca-certificates && while read s d; do \
		ln "$$s" "$$d"; \
	done <${.CURDIR:Q}/certhash.lnk

.include <bsd.port.mk>
