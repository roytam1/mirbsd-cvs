# $MirOS: ports/comms/hylafax/Makefile,v 1.7 2008/10/04 19:03:02 tg Exp $
# $OpenBSD: Makefile,v 1.41 2003/11/11 22:24:19 todd Exp $

BROKEN=			uses old C++ API

COMMENT=		send/receive faxes and share modems
DISTNAME=		hylafax-4.1.5
DASH_VER=		2
CATEGORIES=		comms

HOMEPAGE=		http://www.HylaFAX.org/
MASTER_SITES=		ftp://ftp.hylafax.org/source/

# License: BSD
# http://www.hylafax.org/HylaFAQ/copyright.html
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

RUN_DEPENDS=		:ghostscript-*:print/ghostscript/artifex
LIB_DEPENDS=		tiff::graphics/tiff \
			jpeg::graphics/jpeg

CONFIGURE_STYLE=	simple
USE_GMAKE=		Yes
USE_CXX=		Yes

CONFIGURE_ARGS =	--nointeractive
CONFIGURE_ARGS+=	--with-CC=${_PASS_CC:T:Q}
CONFIGURE_ARGS+=	--with-CXX=${_PASS_CXX:T:Q}
CONFIGURE_ARGS+=        --with-INSTALL=""
CONFIGURE_ARGS+=	--with-PAGESIZE=A4

CONFIGURE_ENV+=		CCOMPILER=${_PASS_CC:T:Q} CXXCOMPILER=${_PASS_CXX:T:Q} \
			GCOPTS="${CFLAGS}" GCXXOPTS="${CXXFLAGS}" \
			PREFIX="${PREFIX}" LOCALBASE="${LOCALBASE}"


FAKE_FLAGS=	ROOT=${WRKINST} ${DESTDIRNAME}=${WRKINST}

SUID_EXES=	${PREFIX}/sbin/faxgetty ${PREFIX}/sbin/faxq \
		${PREFIX}/bin/faxrm ${PREFIX}/bin/faxalter

NO_SYSTRACE=	"test -d '' succeeds"

post-extract:
	cd ${PORTSDIR}/infrastructure/db && install -c -m 555 config.guess \
		config.sub ${WRKSRC}

post-install:
	@chown uucp:dialer ${SUID_EXES}
	@chmod a=rx,u+s ${SUID_EXES}
	${INSTALL_DATA} ${FILESDIR}/hylafax.sh.sample ${PREFIX}/lib/fax

pre-package:
	@${SUDO} rm -f ${WRKINST}/${PREFIX}/hylafax
	@${SUDO} ln -s ${WRKINST}/var/spool/hylafax ${WRKINST}/${PREFIX}/hylafax

post-package:
	@${SUDO} rm -f ${WRKINST}/${PREFIX}/hylafax

.include <bsd.port.mk>
