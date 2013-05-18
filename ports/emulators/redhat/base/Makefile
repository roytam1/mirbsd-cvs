# $MirOS: ports/emulators/redhat/base/Makefile,v 1.5 2006/02/20 20:50:01 tg Exp $
# $OpenBSD: Makefile,v 1.21 2004/03/02 07:49:24 ish Exp $

COMMENT=			Linux compatibility package based on RedHat GNU/Linux 8.0
PKGNAME=	redhat_base-8.0-${PL}
MASTER_SITES=	${MASTER_SITE_REDHAT:=redhat/linux/8.0/en/os/i386/RedHat/RPMS/}
MASTER_SITES0=	${MASTER_SITE_REDHAT:=redhat/linux/updates/8.0/en/os/i386/}
DISTFILES=	${RPMS}
RPMDIR=		${FULLDISTDIR}
RUN_DEPENDS+=	:linux-common-*:emulators/linux-common

RPMS=		glibc-2.3.2-4.80.8.i386.rpm:0 \
		glibc-common-2.3.2-4.80.8.i386.rpm:0 \
		libattr-2.0.8-3.i386.rpm \
		libacl-2.0.11-2.i386.rpm \
		termcap-11.0.1-13.noarch.rpm \
		libtermcap-2.0.8-31.i386.rpm \
		bash-2.05b-5.1.i386.rpm:0 \
		ncurses-5.2-28.i386.rpm \
		zlib-1.1.4-8.8x.i386.rpm:0 \
		fileutils-4.1.9-11.2.i386.rpm:0 \
		binutils-2.13.90.0.2-2.i386.rpm \
		compat-libstdc++-7.3-2.96.110.i386.rpm \
		libstdc++-3.2-7.i386.rpm \
		sh-utils-2.0.12-3.i386.rpm \
		readline-4.3-3.i386.rpm \
		XFree86-libs-4.2.1-23.i386.rpm:0 \
		glib-1.2.10-8.i386.rpm \
		gtk+-1.2.10-22.i386.rpm \
		libjpeg-6b-21.i386.rpm \
		libpng-1.2.2-8.i386.rpm:0 \
		fontconfig-2.0-3.i386.rpm \
		freetype-2.1.2-7.i386.rpm \
		expat-1.95.4-1.i386.rpm

REMOVE_DIRS=	/usr/doc /usr/info /usr/man /usr/share/doc /usr/share/zoneinfo
REMOVE_FILES=	/etc/fonts/fonts.conf /etc/localtime

PATCH_LIST=

do-install:
.for rpm in ${RPMS:S/:0//}
	@cd ${EMDIR}; ${LOCALBASE}/bin/rpm2cpio ${RPMDIR}/${rpm} | cpio -id
.endfor

# Get rid of some unnecessary files and directories.
.for D in ${REMOVE_DIRS}
	@rm -rf ${EMDIR}/${D}
.endfor
.for F in ${REMOVE_FILES}
	@rm -f ${EMDIR}/${F}
.endfor

	@cd ${EMDIR} && ${PATCH} -p0 --forward --quiet -E < ${PATCHDIR}/patch-ldd

# copy in ld.so.conf
	${INSTALL_DATA} ${FILESDIR}/ld.so.conf ${EMDIR}/etc/
	${INSTALL_DATA} ${FILESDIR}/fonts.conf ${EMDIR}/etc/fonts/

# run elf2olf on a few binaries known not to run as elf
	@elf2olf -o linux ${EMDIR}/sbin/ldconfig

# rename ldconfig and install wrapper
	@cp -p ${EMDIR}/sbin/ldconfig ${EMDIR}/sbin/ldconfig.bin
	${INSTALL_SCRIPT} ${FILESDIR}/ldconfig ${EMDIR}/sbin

# make a copy of ld.so, convert to olf and then patch
	@cp -p ${EMDIR}/lib/ld-2.3.2.so ${EMDIR}/usr/bin/ld-2.3.2-olf.so
	@elf2olf -o linux ${EMDIR}/usr/bin/ld-2.3.2-olf.so
	@perl ${FILESDIR}/fix-ldd.pl ${EMDIR}/usr/bin/ld-2.3.2-olf.so

post-install:
# remove setuid root bits, fix ownerships
	@find ${EMDIR} -perm -4000 -exec chmod u-s {} \;
	@find ${EMDIR} -user 5041 -exec chown -h ${BINOWN}:${BINGRP} {} \;

.include <bsd.port.mk>
