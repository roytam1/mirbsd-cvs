# $MirOS: ports/emulators/debian/Makefile,v 1.1 2006/01/18 11:16:47 tg Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:i386 OpenBSD:*:i386

COMMENT=		"Debian GNU/Linux shared libraries"
EMUL=			linux
CATEGORIES=		emulators
DISTNAME=		debian-libs-3.1
FULLPKGNAME=		${DISTNAME}-0
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>

# DFSG compliant
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DIST_SUBDIR=		deb
MASTER_SITE_DEBIAN=	http://ftp.debian.org/pool/main/

MASTER_SITES0=		${MASTER_SITE_DEBIAN:=g/glibc/}
MASTER_SITES1=		${MASTER_SITE_DEBIAN:=e/expat/}
MASTER_SITES2=		${MASTER_SITE_DEBIAN:=f/fontconfig/}
MASTER_SITES3=		${MASTER_SITE_DEBIAN:=f/freetype/}
MASTER_SITES4=		${MASTER_SITE_DEBIAN:=x/xfree86/}
MASTER_SITES5=		${MASTER_SITE_DEBIAN:=z/zlib/}

DISTFILES=		libc6_2.3.2.ds1-22_i386.deb:0 \
			libexpat1_1.95.8-3_i386.deb:1 \
			libfontconfig1_2.3.1-2_i386.deb:2 \
			libfreetype6_2.1.7-2.4_i386.deb:3 \
			libice6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libsm6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libx11-6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libxext6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libxpm4_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libxt6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			xlibs_4.3.0.dfsg.1-14sarge1_all.deb:4 \
			zlib1g_1.2.2-4.sarge.2_i386.deb:5

WRKDIST=		${WRKDIR}/debian-libs
NO_REGRESS=		Yes

BASEDIR=		${PREFIX}/emul/debian

.include <mirports.sys.mk>
.if ${OStype} == "MirBSD"
HAS_DYNEXEC!=		eval $$(uname -l|sed \
			    's/^\#\([0-9]*\)[a-z]\([0-9A-F][0-9A-F]\).*$$/let \
			     major=\1 minor=16\#\2/'); \
			(( (major > 8) || ((major == 8) && (minor > 161)) )) \
			    && echo dynexec || true
.endif

FLAVORS=		${HAS_DYNEXEC}
FLAVOR?=		${HAS_DYNEXEC}

.if ${FLAVOR:L:Mdynexec}
SED_PLIST+=		| sed -e '/^KLUDGE:/d'
LDSO=			ld-linux.so.2
.else
SED_PLIST+=		| sed -e '/^KLUDGE:/s///'
LDSO=			ld-linux.so.2.bin
.endif

do-extract:
	mkdir -p ${WRKDIST}
.for _i in ${DISTFILES:T}
	cd ${WRKDIST}; ar x ${FULLDISTDIR}/${_i:C/:.$//} && tar xzf data.tar.gz
.endfor

do-build:
	sed -e 's!@@BASEDIR@@!${BASEDIR}!g' -e 's!@@LDSO@@!${LDSO}!g' \
	    <${FILESDIR}/run >${WRKSRC}/run

LIBS=			/lib/ld-linux.so.2 \
			/lib/libc.so.6 \
			/lib/libdl.so.2 \
			/lib/libm.so.6 \
			/lib/libpthread.so.0 \
			/usr/X11R6/lib/libICE.so.6 \
			/usr/X11R6/lib/libSM.so.6 \
			/usr/X11R6/lib/libX11.so.6 \
			/usr/X11R6/lib/libXext.so.6 \
			/usr/X11R6/lib/libXpm.so.4 \
			/usr/X11R6/lib/libXt.so.6 \
			/usr/lib/libexpat.so.0 \
			/usr/lib/libfontconfig.so.1 \
			/usr/lib/libfreetype.so.6 \
			/usr/lib/libz.so.1

do-install:
	${INSTALL_DATA_DIR} ${BASEDIR}
.for _i in ${LIBS}
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${WRKDIST}${_i} ${BASEDIR}/
.endfor
.if !${FLAVOR:L:Mdynexec}
	# hack ET_DYN
	cp ${BASEDIR}/ld-linux.so.2 ${BASEDIR}/ld-linux.so.2.bin
	chmod 600 ${BASEDIR}/ld-linux.so.2.bin
	print -n '\02' | dd of=${BASEDIR}/ld-linux.so.2.bin \
	    bs=1 conv=notrunc seek=16
.endif
	chmod ${BINMODE} ${BASEDIR}/ld-linux.so.2*
	${INSTALL_SCRIPT} ${WRKSRC}/run ${BASEDIR}/

.include <bsd.port.mk>
