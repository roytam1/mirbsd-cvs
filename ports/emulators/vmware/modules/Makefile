# $MirOS: ports/emulators/vmware/modules/Makefile,v 1.4 2005/07/07 21:20:51 bsiegert Exp $

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

.if !exists(/sys/sys/ioctl_compat.h)
IGNORE="Fatal: This port requires kernel sources to build"
.endif

COMMENT=			LKMs to allow vmware to run under MirBSD
PKGNAME=	vmware-modules-1.1-0
DISTNAME=	vmware-openbsd-1.1
CATEGORIES=	emulators
MASTER_SITES=	${HOMEPAGE}
HOMEPAGE=	http://monkey.org/~marius/vmware-openbsd/

# Derivative work from publically released VMware stuff (unlicensed).
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	No
PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	No

NO_REGRESS=	Yes

WRKDIST=${WRKDIR}/vmware-openbsd3

do-configure:
	@perl -pi -e 's|_PREFIX_|${PREFIX}|g' ${WRKSRC}/util/vmware-run.c

pre-install:
	@sed -e "s|@PREFIX@|${TRUEPREFIX}|g" ${FILESDIR}/vmware-modules.sh > \
		${WRKBUILD}/vmware-modules.sh

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/vmware
	${INSTALL_DATA_DIR} ${PREFIX}/lib/vmware/modules
	${INSTALL_DATA_DIR} ${PREFIX}/lib/vmware/bin
	${INSTALL_DATA_DIR} ${PREFIX}/libexec
	${INSTALL_DATA} ${WRKBUILD}/README \
		${PREFIX}/share/doc/vmware/README.NetBSD
	${INSTALL_DATA} ${WRKBUILD}/README.OpenBSD \
		${PREFIX}/share/doc/vmware/README.MirBSD.Modules
	${INSTALL_DATA} ${WRKBUILD}/source/linuxrtc/linuxrtc.o \
		${WRKBUILD}/source/vmmon/vmmon.o \
		${WRKBUILD}/source/vmnet/if_hub.o \
		${PREFIX}/lib/vmware/modules
	${INSTALL_PROGRAM} ${WRKBUILD}/vmware-any-any-update37/update \
		${PREFIX}/lib/vmware/bin
	${INSTALL_PROGRAM} ${WRKBUILD}/util/vmware-run ${PREFIX}/lib/vmware/bin
.for S in linuxrtc vmmon vmnet
	${INSTALL_SCRIPT} ${FILESDIR}/vmware-${S}_load.sh \
		${FILESDIR}/vmware-${S}_unload.sh \
		${PREFIX}/libexec
.endfor
	${INSTALL_SCRIPT} ${WRKBUILD}/vmware-modules.sh \
		${PREFIX}/bin/vmware-modules

.include <bsd.port.mk>
