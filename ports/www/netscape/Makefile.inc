# $OpenBSD: Makefile.inc,v 1.21 2004/05/01 14:29:17 sturm Exp $
#
# Relevant URLs:	http://www.bsdi.com/netscape/
#			http://www.fortify.net/

# Subdirectory MUST define DIRNAME, LOCATION and PROGRAM_V.

.if ${EMUL} == "linux"
BUILD_DEPENDS=		:redhat_base-*:emulators/redhat/base 
RUN_DEPENDS=		${BUILD_DEPENDS}
SUPPORTED=		supported
ONLY_FOR_PLATFORM=	OpenBSD:i386 MirBSD:i386
.endif

.if ${EMUL} == "sunos"
ONLY_FOR_PLATFORM=	OpenBSD:sparc
.endif

.if ${EMUL} == "bsdos"
ONLY_FOR_PLATFORM=	OpenBSD:i386
.endif

SUPPORTED?=		unsupported

CATEGORIES=     	www
MASTER_SITES= \
	ftp://ftp.netscape.com/pub/$S/ \
	ftp://uiarchive.uiuc.edu/pub/www/netscape/$S/ \
	ftp://netscape.Mirror.McGill.CA/pub/mirrors/ftp.netscape.com/pub/$S/ \
	ftp://ftp.the.net/pub/mirrors/ftp.netscape.com/pub/$S/ \
	ftp://sunsite.doc.ic.ac.uk/packages/netscape/pub/$S/ \
	ftp://ftp-de.netscape.com/pub/$S/ \
	ftp://nic.funet.fi/pub/mirrors/ftp.netscape.com/pub/$S/
MASTER_SITES0= \
	ftp://archive.netscape.com/pub/$S/
MASTER_SITES1=	ftp://ftp.fortify.net/pub/Fortify/ \
		ftp://ftp.sunet.se/pub/security/tools/net/Fortify/ \
		ftp://ftp.funet.fi/pub/crypt/mirrors/fortify/ \
		ftp://ftp.it.net.au/mirrors/Fortify/
S= communicator/english/${PROGRAM_V}/unix/${SUPPORTED}/${LOCATION}
DIST_SUBDIR=	netscape

HOMEPAGE=	http://www.netscape.com/

PERMIT_PACKAGE_CDROM=	"Commercial software"
PERMIT_PACKAGE_FTP=	"Commercial software"
PERMIT_DISTFILES_CDROM=	"Commercial software"
PERMIT_DISTFILES_FTP=	"Commercial software"

WRKDIST=	${WRKDIR}

.if !defined(NO_WARNINGS)
pre-fetch:
.if ${EMUL} == "bsdos"
	@echo ""
	@echo "  WARNING: This application requires a kernel compiled with"
	@echo "           'option COMPAT_BSDOS' for proper operation.  The"
	@echo "           GENERIC kernel contains this option."
	@echo ""
.endif
.if ${EMUL} == "linux"
	@echo ""
	@echo "  WARNING: This application requires a kernel compiled with"
	@echo "           'option COMPAT_LINUX' for proper operation.  The"
	@echo "           GENERIC kernel contains this option."
	@echo ""
.endif
.if ${EMUL} == "sunos"
	@echo ""
	@echo "  WARNING: This application requires a kernel compiled with"
	@echo "           'option COMPAT_SUNOS' and SunOS shared libraries"
	@echo "           for proper operation, see compat_sunos(8) for"
	@echo "           further details."
	@echo ""
.endif
.endif

.if defined(NEEDS_FORTIFY)
do-build:
	@cd ${WRKDIR}/${FORTIFY}/src/common && \
	env ${MAKE_ENV} make ${MAKE_FLAGS} ${MAKEFILE} all && \
	cd ${WRKDIR}/${FORTIFY}/src/cmdline && \
	env ${MAKE_ENV} make ${MAKE_FLAGS} ${MAKEFILE} fortify
.endif

do-install:
	@cd ${WRKDIR}/${DIRNAME} && ${MAKE_ENV} ./ns-install

post-install:
.if defined(NEEDS_FORTIFY)
	@cp ${PREFIX}/netscape/netscape ${PREFIX}/netscape/netscape_nis
	@cp ${PREFIX}/netscape/netscape_dns ${PREFIX}/netscape/netscape
	@rm -f ${PREFIX}/netscape/netscape_dns
	@cd ${WRKDIR}/${FORTIFY} && \
	ln -sf languages/English Messages && \
	{ echo yes ; echo no ; echo no; } \
	| src/cmdline/fortify >/dev/null ${PREFIX}/netscape/netscape
	@cd ${WRKDIR}/${FORTIFY} && \
	{ echo yes ; echo no ; echo no; } \
	| src/cmdline/fortify >/dev/null ${PREFIX}/netscape/netscape_nis
.endif
	@sed -e 's#@netscape_home@#${TRUEPREFIX}/netscape#' \
	     -e 's#@prefix@#${TRUEPREFIX}#' \
	 ${FILESDIR}/netscape.${MACHINE_ARCH} > ${WRKDIR}/netscape
	${INSTALL_SCRIPT} ${WRKDIR}/netscape ${PREFIX}/bin
