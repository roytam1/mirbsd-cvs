# $MirOS: ports/security/pgp+/Makefile,v 1.10 2008/11/08 23:04:04 tg Exp $

COMMENT=		Pretty Good Privacy 2.6.3in
DISTNAME=		pgp263in010323
CATEGORIES=		security
PKGNAME=		pgp-2.6.3in-${DASH_VER}
DASH_VER=		3
EXTRACT_SUFX=		.tgz
HOMEPAGE=		ftp://ftp.iks-jena.de/pub/mitarb/lutz/crypt/software/pgp/pgp263in/
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.org>
MASTER_SITES=		${HOMEPAGE}

# see ${FILESDIR}/README.MirPorts for details
PERMIT_PACKAGE_CDROM=	"no commercial use of the IDEA patent"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no commercial use of the IDEA patent"
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/pgp263in
WRKSRC=			${WRKDIST}/src

NO_REGRESS=		Yes

# library and doc files to install
LIBFILES=		config.txt de.hlp en.hlp es.hlp fr.hlp keys.asc \
			language.txt language.txt.Sie pgp.hlp
LIBDOCS=		readme.1st setup.doc
DOCS=			appnote.doc blurb.txt changes.doc keyserv.doc \
			mitlicen.txt pgformat.doc pgp262i.dif pgp263i.dif \
			pgp263in.changes pgpdoc1.txt pgpdoc2.txt politic.doc \
			przon26i.asc README.MirPorts
PGP_DOC_DIR=		${PREFIX}/share/doc/pgp

# Before the build figure out if we are on a big endian machine or not
pre-build:
	@print '#include <machine/endian.h>\npgpin: BYTE_ORDER' | \
	    ${_PASS_CC:Q} -E - >${WRKDIR}/.endian.out
	@if fgrep -q 'pgpin: 4321' ${WRKDIR}/.endian.out; then \
		echo -DHIGHFIRST >${WRKDIR}/.endian; \
	else \
		cp /dev/null ${WRKDIR}/.endian; \
	fi

do-build:
	@cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE} -f makefile all \
	    CC=${_PASS_CC:T:Q} CFLAGS=${CFLAGS:M*:Q}" -DUNIX -DPORTABLE \
	    -DMERRITT -DIDEA32 -DPGP_DOC_DIR=\\\"${PGP_DOC_DIR}\\\" \
	    -DMAX_NAMELEN=255 $$(<${WRKDIR}/.endian)" \
	    LD=${_PASS_CC:T:Q} LDFLAGS=${LDSTATIC:M*:Q}
	cp ${FILESDIR}/README.MirPorts ${WRKDIST}/doc/

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/pgp
	${INSTALL_DATA_DIR} ${PGP_DOC_DIR}
	${INSTALL_PROGRAM} ${WRKSRC}/pgp ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKDIST}/doc/pgp.1 ${PREFIX}/man/man1/
	cd ${WRKDIST} && \
	    ${INSTALL_DATA} ${LIBDOCS} ${PGP_DOC_DIR}/ && \
	    ${INSTALL_DATA} ${LIBFILES} ${PREFIX}/lib/pgp/ && \
	    cd doc && ${INSTALL_DATA} ${DOCS} ${PGP_DOC_DIR}/

.include <bsd.port.mk>
