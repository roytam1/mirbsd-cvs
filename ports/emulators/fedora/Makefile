# $MirOS: ports/emulators/fedora/Makefile,v 1.4 2009/03/29 13:04:00 tg Exp $
# $OpenBSD: Makefile,v 1.8 2008/06/12 16:33:21 miod Exp $
# $OpenBSD: Makefile,v 1.3 2007/09/16 00:45:13 merdely Exp $
# $OpenBSD: Makefile.inc,v 1.1.1.1 2006/10/17 22:33:44 sturm Exp $

ONLY_FOR_PLATFORM=	MirBSD:*:i386 OpenBSD:*:i386
EMUL=			linux
CATEGORIES=		emulators
COMMENT=		Linux compatibility package based on Fedora Core 4
PKGNAME=		fedora-libs-4.0-${DASH_VER}
DASH_VER=		1

PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes
PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes

.include <mirports.sys.mk>
.if !defined(SUDO) || empty(SUDO)
IGNORE+=		"requires use of SUDO=sudo"
.endif

#MASTER_SITE_FEDORA=	http://download.fedora.redhat.com/pub/fedora/linux/core/ \
#			http://mirror.aarnet.edu.au/pub/fedora/linux/core/ \
#			ftp://ftp.funet.fi/pub/mirrors/ftp.redhat.com/pub/fedora/linux/core/
MASTER_SITE_FEDORA=	http://archives.fedoraproject.org/pub/archive/fedora/linux/core/

MASTER_SITES=		${MASTER_SITE_FEDORA:=4/i386/os/Fedora/RPMS/}
MASTER_SITES0=		${MASTER_SITE_FEDORA:=updates/4/i386/}
DISTFILES=		${RPMS}
RPMDIR=			${FULLDISTDIR}
FEDORADIR=		${PREFIX}/emul/fedora
DIST_SUBDIR=		rpm
EXTRACT_ONLY=
BUILD_DEPENDS+=		::converters/rpm2cpio

NO_BUILD=		Yes
NO_LIBTOOLISE_PLIST=	Yes
NO_SHARED_LIBS=		Yes
NO_REGRESS=		Yes

RPMS=		atk-1.9.1-1.i386.rpm \
		bash-3.0-31.i386.rpm \
		binutils-2.15.94.0.2.2-2.1.i386.rpm:0 \
		compat-libstdc++-296-2.96-132.fc4.i386.rpm \
		compat-libstdc++-33-3.2.3-47.fc4.i386.rpm \
		expat-1.95.8-6.i386.rpm \
		file-4.16-fc4.1.i386.rpm:0 \
		fontconfig-2.2.3-13.i386.rpm \
		freetype-2.1.9-2.i386.rpm \
		gdk-pixbuf-0.22.0-18.fc4.2.i386.rpm:0 \
		glib-1.2.10-16.i386.rpm \
		glib2-2.6.6-1.i386.rpm:0 \
		glibc-2.3.6-3.i386.rpm:0 \
		glibc-common-2.3.6-3.i386.rpm:0 \
		gtk+-1.2.10-39.i386.rpm \
		gtk2-2.6.10-2.fc4.4.i386.rpm:0 \
		libacl-2.2.32-1.FC4.2.i386.rpm:0 \
		libattr-2.4.24-1.FC4.1.i386.rpm:0 \
		libgcc-4.0.2-8.fc4.i386.rpm:0 \
		libjpeg-6b-34.i386.rpm \
		libpng-1.2.8-2.i386.rpm \
		libstdc++-4.0.2-8.fc4.i386.rpm:0 \
		libtermcap-2.0.8-41.i386.rpm \
		libtiff-3.7.1-6.fc4.3.i386.rpm:0 \
		ncurses-5.4-19.fc4.i386.rpm:0 \
		openmotif21-2.1.30-14.i386.rpm \
		pango-1.8.1-2.i386.rpm \
		readline-5.0-3.i386.rpm \
		termcap-5.4-7fc4.noarch.rpm:0 \
		xorg-x11-deprecated-libs-6.8.2-37.FC4.49.2.1.i386.rpm:0 \
		xorg-x11-libs-6.8.2-37.FC4.49.2.1.i386.rpm:0 \
		zlib-1.2.2.2-5.fc4.i386.rpm:0

REMOVE_DIRS=		usr/X11R6/man /usr/doc /usr/info /usr/man \
			/usr/share/doc /usr/share/man /usr/share/zoneinfo
REMOVE_FILES=		/etc/localtime

PATCH_LIST=

USE_CPIO=		mircpio
.if ${OStype} == "MirBSD"
.  if ${OSrev} > 10
USE_CPIO=		/bin/cpio
.  elif ${OSrev} == 10
.    if ${OSver:E} > 161
USE_CPIO=		/bin/cpio
.    endif
.  endif
.endif
.if ${USE_CPIO} == "mircpio"
BUILD_DEPENDS+=		:paxmirabilis->=20081030:archivers/mircpio
.endif

do-install:
	${INSTALL_DATA_DIR} ${FEDORADIR}/usr/{,X11R6/}lib
.for rpm in ${RPMS:S/:0//}
	cd ${FEDORADIR}; rpm2cpio ${RPMDIR}/${rpm} | ${USE_CPIO} -mid
.endfor

# get rid of some unnecessary files and directories
.for D in ${REMOVE_DIRS}
	rm -rf ${FEDORADIR}/${D}
.endfor
.for F in ${REMOVE_FILES}
	rm -f ${FEDORADIR}/${F}
.endfor

	mkdir ${FEDORADIR}/dev; \
		ln -s /dev/console ${FEDORADIR}/dev/tty0; \
		ln -s /dev/ttyC0 ${FEDORADIR}/dev/tty1; \
		ln -s /dev/ttyC1 ${FEDORADIR}/dev/tty2; \
		ln -s /dev/ttyC2 ${FEDORADIR}/dev/tty3; \
		ln -s /dev/ttyC3 ${FEDORADIR}/dev/tty4; \
		ln -s /dev/ttyC4 ${FEDORADIR}/dev/tty5; \
		ln -s /dev/sound ${FEDORADIR}/dev/dsp; \
		ln -s /dev/null ${FEDORADIR}/dev/null

	cd ${FEDORADIR} && \
	    ${PATCH} -p0 --forward --quiet -E <${PATCHDIR}/patch-ldd
	${INSTALL_DATA} ${FILESDIR}/ld.so.conf ${FEDORADIR}/etc
	mv ${FEDORADIR}/sbin/ldconfig ${FEDORADIR}/sbin/ldconfig.bin
	${INSTALL_SCRIPT} ${FILESDIR}/ldconfig ${FEDORADIR}/sbin
	cp -p ${FEDORADIR}/lib/ld-2.3.6.so ${FEDORADIR}/usr/bin/ld-2.3.6-elf.so

# need old linuxthreads libraries
	rm ${FEDORADIR}/lib/libpthread*
	mv ${FEDORADIR}/lib/obsolete/linuxthreads/* ${FEDORADIR}/lib
	rm -fr ${FEDORADIR}/lib/obsolete
# fix fontconfig search path
	cd ${FEDORADIR}/etc/fonts && ${PATCH} -p0 --forward --quiet -E \
	    <${PATCHDIR}/patch-etc_fonts_fonts_conf
# better safe than sorry
	find ${FEDORADIR} -perm -4000 | xargs -r chmod u-s
	find ${FEDORADIR} \( -user 37 -o -user 5041 -o -group 37 \) -print | \
	    xargs -r chown -h root:wheel

.include <bsd.port.mk>
