# $MirOS: ports/emulators/vmware/vmware3/Makefile,v 1.4 2005/07/07 21:20:51 bsiegert Exp $
# $OpenBSD$

ONLY_FOR_PLATFORM=	OpenBSD:*:i386 MirBSD:*:i386

COMMENT=			commercial x86-32 machine emulator
DISTNAME=	VMware-workstation-3.2.1-2242
PKGNAME=	vmware-3.2.1_2242-0
CATEGORIES=	emulators
MASTER_SITES=	http://vmware-chil.www.conxion.com/software/ \
		http://vmware-svca.www.conxion.com/software/ \
		http://vmware-heva.www.conxion.com/software/
HOMEPAGE=	http://www.vmware.com/

# Restrictive
PERMIT_DISTFILES_CDROM=	No
PERMIT_DISTFILES_FTP=	No
PERMIT_PACKAGE_CDROM=	No
PERMIT_PACKAGE_FTP=	No

NO_BUILD=	Yes
NO_REGRESS=	Yes
USE_X11=	Yes

BUILD_DEPENDS+=	::emulators/redhat/base \
		::emulators/vmware/modules
RUN_DEPENDS+=	${BUILD_DEPENDS}

WRKDIST=	${WRKDIR}/vmware-distrib

LIB_DATA_DIRS=	configurator \
		isoimages \
		messages/chef \
		messages/ja \
		messages/jive \
		smb/codepages \
		help \
		xkeymap

post-patch:
	@chmod 755 ${WRKBUILD}/bin/vmware
	@${LOCALBASE}/lib/vmware/bin/update ${WRKBUILD}/bin/vmware

do-install:
	${INSTALL_DATA_DIR} ${PREFIX}/lib/vmware
	${INSTALL_PROGRAM_DIR} ${PREFIX}/lib/vmware/bin
	${INSTALL_SCRIPT} ${WRKBUILD}/bin/vmware \
	    ${PREFIX}/lib/vmware/bin
	${INSTALL_SCRIPT} ${WRKBUILD}/bin/vmnet-netifup ${PREFIX}/bin
	${INSTALL_SCRIPT} ${WRKBUILD}/lib/bin/* ${PREFIX}/lib/vmware/bin
	@sed -e "s|@PREFIX@|${TRUEPREFIX}|g" ${FILESDIR}/vmware.sh \
	    >${PREFIX}/bin/vmware
	@chown ${BINOWN} ${PREFIX}/bin/vmware
	@chgrp ${BINGRP} ${PREFIX}/bin/vmware
	@chmod ${BINMODE} ${PREFIX}/bin/vmware
	${INSTALL_DATA_DIR} ${PREFIX}/lib/vmware/licenses/{site,user}
	${INSTALL_DATA} ${WRKBUILD}//lib/licenses/user/license.ws.3.0 \
	    ${PREFIX}/lib/vmware/licenses/user/
.for d in ${LIB_DATA_DIRS}
	${INSTALL_DATA_DIR} ${PREFIX}/lib/vmware/${d}
	${INSTALL_DATA} ${WRKBUILD}/lib/${d}/* ${PREFIX}/lib/vmware/${d}
.endfor
	${INSTALL_DATA_DIR} ${PREFIX}/share/doc/vmware
	${INSTALL_DATA_DIR} ${PREFIX}/share/examples/vmware
	${INSTALL_DATA} ${FILESDIR}/README.OpenBSD \
	    ${PREFIX}/share/doc/vmware/README.MirBSD
	@sed -e "s|@PREFIX@|${TRUEPREFIX}|g" ${FILESDIR}/config \
	    >${PREFIX}/share/examples/vmware/config

.include <bsd.port.mk>
