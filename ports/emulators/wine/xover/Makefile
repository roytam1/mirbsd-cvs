# $MirOS: ports/emulators/wine/xover/Makefile,v 1.4 2005/07/07 21:20:55 bsiegert Exp $

BROKEN=		243 UNIMPL linux_sys_set_thread_area
# missing emulated syscalls

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386
EMUL=			linux

USE_X11=	Yes
NO_SYSTRACE=	"weird Linuxulator stuff"
IS_INTERACTIVE=	Yes

COMMENT=			experimental: Microsoft Windows emulator Crossover Office
VERSION=	2.0.0
DISTNAME=	xover-${VERSION}
PKGNAME=	xover-linux-${VERSION}-0
CATEGORIES=	emulators

HOMEPAGE=	http://www.codeweavers.com/products/office/

PERMIT_PACKAGE_CDROM=	"commercial software"
PERMIT_PACKAGE_FTP=	"commercial software"
PERMIT_DISTFILES_CDROM=	"commercial software"
PERMIT_DISTFILES_FTP=	"commercial software"

DISTFILES=	install-crossover-office-${VERSION}.sh
EXTRACT_CASES+=	*.sh) \
		    eval $$(head -150 ${DISTDIR}/$$archive|grep '^skip'); \
		    tail +$$skip ${DISTDIR}/$$archive | gzip -dc | \
		    (cd ${WRKDIST} && tar xf -) ;; \

BUILD_DEPENDS=	:redhat_base->=6.2:emulators/redhat/base
RUN_DEPENDS=	${BUILD_DEPENDS}

NO_BUILD=	Yes
NO_REGRESS=	Yes

WRKDIST=	${WRKDIR}/${DISTNAME}

FETCH_MANUALLY = " Crossover Office is commercial software. After purchasing it at"
FETCH_MANUALLY+= "     ${HOMEPAGE}"
FETCH_MANUALLY+= " place the file ${DISTFILES}"
FETCH_MANUALLY+= " into ${DISTDIR} and run make again."
FETCH_MANUALLY+= ""

CX_ROOT=	${PREFIX}/cxoffice

pre-extract:
	mkdir -p ${WRKDIST}

pre-install:
	@${INSTALL_DATA_DIR} ${CX_ROOT}

do-install:
	cp -Rp ${WRKSRC}/{bin,doc,etc,lib,support} ${CX_ROOT}
	chmod -R a+x ${CX_ROOT}/bin ${CX_ROOT}/lib
	chmod a+x ${CX_ROOT}/support/templates/dotwine/setup/setup
	${INSTALL_DATA} ${CX_ROOT}/support/templates/cxoffice.conf \
	    ${CX_ROOT}/etc/
	chmod 755 ${CX_ROOT}/etc
	CX_ROOT=${CX_ROOT} sudo -H -u root \
	    ${CX_ROOT}/support/templates/dotwine/setup/setup \
	    --create --updater /usr/bin/true ${CX_ROOT}/support/dotwine
	@rm -f ${.CURDIR}/wineloader.core

.include <bsd.port.mk>
