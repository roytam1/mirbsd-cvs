# $MirOS: ports/emulators/debian/Makefile,v 1.5 2006/09/14 00:09:09 tg Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:i386 OpenBSD:*:i386

COMMENT=		Debian GNU/Linux shared libraries
EMUL=			linux
CATEGORIES=		emulators
DISTNAME=		debian-libs-3.1
FULLPKGNAME=		${DISTNAME}-3
RESPONSIBLE=		Thorsten Glaser <tg@mirbsd.de>
RUN_DEPENDS+=		:linux-common-*:emulators/linux-common

# DFSG compliant
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

DIST_SUBDIR=		deb
MASTER_SITES0=		${MASTER_SITE_DEBIAN:=g/glibc/}
MASTER_SITES1=		${MASTER_SITE_DEBIAN:=e/expat/}
MASTER_SITES2=		${MASTER_SITE_DEBIAN:=f/fontconfig/}
MASTER_SITES3=		${MASTER_SITE_DEBIAN:=f/freetype/}
MASTER_SITES4=		${MASTER_SITE_DEBIAN:=x/xfree86/}
MASTER_SITES5=		${MASTER_SITE_DEBIAN:=z/zlib/}
MASTER_SITES6=		${MASTER_SITE_DEBIAN:=x/xrender/}
MASTER_SITES7=		${MASTER_SITE_DEBIAN:=g/gcc-3.3/}

DISTFILES=		libc6_2.3.2.ds1-22sarge4_i386.deb:0 \
			libexpat1_1.95.8-3_i386.deb:1 \
			libfontconfig1_2.3.1-2_i386.deb:2 \
			libfreetype6_2.1.7-6_i386.deb:3 \
			libice6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libsm6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libx11-6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libxext6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libxft1_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libxpm4_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			libxt6_4.3.0.dfsg.1-14sarge1_i386.deb:4 \
			xlibs_4.3.0.dfsg.1-14sarge1_all.deb:4 \
			zlib1g_1.2.2-4.sarge.2_i386.deb:5 \
			libxrender1_0.8.3-7_i386.deb:6 \
			libstdc++5_3.3.5-13_i386.deb:7

WRKDIST=		${WRKDIR}/debian-libs
NO_BUILD=		Yes
NO_REGRESS=		Yes

BASEDIR=		${PREFIX}/emul/debian/dbl

do-extract:
	mkdir -p ${WRKDIST}
.for _i in ${DISTFILES:T}
	cd ${WRKDIST}; ar x ${FULLDISTDIR}/${_i:C/:.$//} && tar xzf data.tar.gz
.endfor

LIBS=			/lib/ld-linux.so.2 \
			/lib/libc.so.6 \
			/lib/libcrypt.so.1 \
			/lib/libdl.so.2 \
			/lib/libm.so.6 \
			/lib/libnsl.so.1 \
			/lib/libnss_compat.so.2 \
			/lib/libnss_dns.so.2 \
			/lib/libnss_files.so.2 \
			/lib/libpthread.so.0 \
			/lib/libresolv.so.2 \
			/lib/librt.so.1 \
			/lib/libutil.so.1 \
			/usr/X11R6/lib/libICE.so.6 \
			/usr/X11R6/lib/libSM.so.6 \
			/usr/X11R6/lib/libX11.so.6 \
			/usr/X11R6/lib/libXext.so.6 \
			/usr/X11R6/lib/libXft.so.1 \
			/usr/X11R6/lib/libXpm.so.4 \
			/usr/X11R6/lib/libXt.so.6 \
			/usr/lib/libXrender.so.1 \
			/usr/lib/libexpat.so.0 \
			/usr/lib/libfontconfig.so.1 \
			/usr/lib/libfreetype.so.6 \
			/usr/lib/libstdc++.so.5 \
			/usr/lib/libz.so.1

do-install:
	${INSTALL_DATA_DIR} ${BASEDIR}
.for _i in ${LIBS}
	chmod u+w ${WRKDIST}${_i}
	perl -i -pe 's!/lib/ld-linux\.so\.2!/dbl/ld-linux.so.2!' ${WRKDIST}${_i}
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 \
	    ${WRKDIST}${_i} ${BASEDIR}/
.endfor
	chmod ${BINMODE} ${BASEDIR}/ld-linux.so.2

.include <bsd.port.mk>
