# $MirOS: ports/emulators/kqemu/Makefile,v 1.4 2008/11/16 20:07:21 tg Exp $
# $OpenBSD: Makefile,v 1.5 2008/04/29 20:38:03 todd Exp $

ONLY_FOR_PLATFORMS=	\
			MirBSD:*:i386 \
			OpenBSD:*:amd64 \
			OpenBSD:*:i386

COMMENT=		QEMU accelerator module
DISTNAME=		kqemu-1.3.0pre11
DASH_VER=		2
CATEGORIES=		emulators
HOMEPAGE=		http://fabrice.bellard.free.fr/qemu/
MASTER_SITES=		${HOMEPAGE}

# GPLv2
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

USE_GMAKE=		Yes
CONFIGURE_STYLE=	simple
CONFIGURE_ARGS=		--prefix=${PREFIX:Q} \
			--cc=${_PASS_CC:T:Q} \
			--host-cc=${_PASS_CC:T:Q} \
			--make=${MAKE_PROGRAM:Q}

INSTDIR=		${PREFIX}/libdata
SUBST_VARS=		INSTDIR
PLIST=			${PKGDIR}/PLIST.${OStype}
MESSAGE=		${PKGDIR}/MESSAGE.${OStype}

NO_REGRESS=		Yes

FILES=			Makefile.openbsd kqemu-openbsd.c
.if ${OStype} == "OpenBSD"
LKMS=			kqemu.o kqemu_mp.o
.else
LKMS=			kqemu.ko
.endif

post-extract:
	cd ${FILESDIR} && cp ${FILES} ${WRKSRC}/
	cp ${FILESDIR}/scn.c ${WRKSRC}/common/
	cd ${WRKSRC} && cp kqemu-openbsd.c kqemu-openbsd-mp.c

do-build:
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} /usr/bin/make \
	    ${MAKE_FLAGS} -f Makefile.openbsd
.if ${OStype} == "OpenBSD"
	cd ${WRKBUILD} && ${SETENV} ${MAKE_ENV} /usr/bin/make \
	    ${MAKE_FLAGS} -f Makefile.openbsd MP=1
.endif

do-install:
	${INSTALL_DATA_DIR} ${INSTDIR}
	cd ${WRKBUILD} && ${INSTALL_DATA} ${LKMS} ${INSTDIR}/

.include <bsd.port.mk>
