# $MirOS: ports/security/pgp+/Makefile,v 1.5 2005/11/07 20:38:44 tg Exp $

COMMENT=			Pretty Good Privacy 2.6.3in
DISTNAME=	pgp263in010323
CATEGORIES=	security
PKGNAME=	pgp-2.6.3in-1
EXTRACT_SUFX=	.tgz
HOMEPAGE=	ftp://ftp.iks-jena.de/pub/mitarb/lutz/crypt/software/pgp/pgp263in/
RESPONSIBLE=	Thorsten "mirabile" Glaser <tg@66h.42h.de>
MASTER_SITES=	${HOMEPAGE}

# see ${FILESDIR}/README.MirPorts for details
PERMIT_PACKAGE_CDROM=	"no commercial use of the IDEA patent"
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	"no commercial use of the IDEA patent"
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=	${WRKDIR}/pgp263in
WRKSRC=		${WRKDIST}/src

# library and doc files to install
LIBFILES=	config.txt de.hlp en.hlp es.hlp fr.hlp keys.asc \
		language.txt language.txt.Sie pgp.hlp
LIBDOCS=	readme.1st setup.doc
DOCS=		appnote.doc blurb.txt changes.doc keyserv.doc mitlicen.txt \
		pgformat.doc pgp262i.dif pgp263i.dif pgp263in.changes \
		pgpdoc1.txt pgpdoc2.txt politic.doc przon26i.asc
PGP_DOC_DIR=	${PREFIX}/share/doc/pgp

PATCH_LIST=	patch-src_fileio_c patch-src_pgp_c

DOCFILE=	README.MirPorts
DOCS+=		${DOCFILE}

# Before the build figure out if we are on a big endian machine or not
pre-build:
	@echo "#include <machine/endian.h>" > ${WRKDIR}/.endian.c
	@echo "BYTE_ORDER" >> ${WRKDIR}/.endian.c
	@${CC} -E ${WRKDIR}/.endian.c > ${WRKDIR}/.endian.out
	@if { grep -q 4321 ${WRKDIR}/.endian.out; } then \
	   echo -DHIGHFIRST > ${WRKDIR}/.endian; \
	 else \
	   cp /dev/null ${WRKDIR}/.endian; \
	 fi

do-build:
	@cd ${WRKSRC} && ${SETENV} ${MAKE_ENV} ${MAKE} -f makefile all \
	    CC="${CC}" CFLAGS="${CFLAGS} -DUNIX -DPORTABLE -DMERIT \
	    -DIDEA32 -DPGP_DOC_DIR=\\\"${PGP_DOC_DIR}\\\" \
	    -DMAX_NAMELEN=255 `cat ${WRKDIR}/.endian`" \
	    LD="${CC}" LDFLAGS="${LDSTATIC}"
	cp ${FILESDIR}/${DOCFILE} ${WRKDIST}/doc/

NO_REGRESS=	Yes

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/pgp
	${INSTALL_DATA_DIR} ${PGP_DOC_DIR}
	${INSTALL_PROGRAM} ${WRKSRC}/pgp ${PREFIX}/bin/
	${INSTALL_MAN} ${WRKDIST}/doc/pgp.1 ${PREFIX}/man/man1/
	cd ${WRKDIST}; ${INSTALL_DATA} ${LIBDOCS} ${PGP_DOC_DIR}/
	cd ${WRKDIST}; ${INSTALL_DATA} ${LIBFILES} ${PREFIX}/lib/pgp/
	cd ${WRKDIST}/doc; ${INSTALL_DATA} ${DOCS} ${PGP_DOC_DIR}/

.include <bsd.port.mk>
