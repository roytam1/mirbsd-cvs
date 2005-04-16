# $MirOS: X11/Makefile,v 1.12 2005/03/29 00:12:15 tg Exp $

.include <bsd.own.mk>
.include "${BSDSRCDIR}/Makefile.inc"

SUBOBJDIR!=	readlink ${.OBJDIR} || ( cd ${.OBJDIR} && pwd )
RELEASEDIR?=	${BSDRELDIR}/rel

BINDIST=	programs/Xserver/hw/xfree86/etc/bindist
HOSTDEF=	xc/${BINDIST}/OpenBSD-${MACHINE}/host.def
CONFHOSTDEF=	xc/config/cf/host.def
XCONFIG=	xc/${BINDIST}/OpenBSD-${MACHINE}/XF86Config
LOCALAPPX=	/usr/local/lib/X11
LOCALAPPD=	${LOCALAPPX}/app-defaults
REALAPPD=	/etc/X11/app-defaults

DIROWN?=	root
DIRGRP?=	wheel

.include <bsd.obj.mk>

.if make(obj)
SUBDIR=		extras
.  include <bsd.subdir.mk>
.endif

all: ${_STFILE_SUB}
	cd ${.CURDIR} && exec ${_STCMD_SUB} ${MAKE} compile

build:
	cd ${.CURDIR} && exec ${MAKE} all
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} install
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} fix-appd

b-r:
	# Test if the targets are mounted suitable for root (BTSTF)
.for _dir in ${BSDOBJDIR} ${BSDRELDIR}
	mkdir -p ${_dir} || ${SUDO} mkdir -p ${_dir}
	${SUDO} touch ${_dir}/permissions.test
	${SUDO} chown root:wheel ${_dir}/permissions.test
	${SUDO} rm ${_dir}/permissions.test
.endfor
	touch ${BSDOBJDIR}/permissions.test && rm ${BSDOBJDIR}/permissions.test
	@echo ============================================================
	@date
	@echo ============================================================
	cd ${.CURDIR} && ${MAKE} obj && exec ${MAKE} check-objdir
	cd ${.CURDIR} && exec ${MAKE} build
	cd ${.CURDIR} && exec ${MAKE} release
	@echo ============================================================
	@echo Build and Release for the X-Window System complete.
	@date; uname -a
	@echo ============================================================

compile:
	rm -f ${CONFHOSTDEF}
	${INSTALL} ${HOSTDEF} ${CONFHOSTDEF}
.if ${MKC_USAP:L} != "yes"
	echo '#define Freetype2BuildDefines	'\
	    '-DTT_CONFIG_OPTION_BYTECODE_INTERPRETER' >>${CONFHOSTDEF}
.endif
.if defined(NOFONTS) && ${NOFONTS:L} != "no"
	echo "#define BuildFonts		NO" >>${CONFHOSTDEF}
.endif
	cd xc && exec ${MAKE} World \
	    WORLDOPTS="CC=${CC:Q} CXX=${CXX:Q} COPTS=${COPTS:Q}" \
	    CC="${CC}" CXX="${CXX}" COPTS="${COPTS}"
	# We cannot yet auto-generate this manpage correctly
	cd xc/doc/man/GL/gl && if [ -e glMultMatrix._man ]; then \
		neqn <glMultMatrix._man | tbl | nroff -man \
		    >glMultMatrix.0.fixed; \
	fi
	cd ${.CURDIR}/extras && ${MAKE} depend && exec ${MAKE}

install:
	d="${DESTDIR}"; cd $${d:-/}; [[ -n $$d ]] || d="/:/*"; \
	    env WRITEDIR="$$d" NOWRITEDIR="${SUBOBJDIR}" ${EXTRA_ENV} \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}
	cd ${.CURDIR} && exec ${_STCMD_DEST} ${MAKE} do-install
	sleep 1; rm ${_STFILE_DEST}

do-install:
	cd xc && ${MAKE} install CC="${CC}" && exec ${MAKE} install.man
	# Install fixed copy of manual page
	cd xc/doc/man/GL/gl && if [ -e glMultMatrix.0.fixed ]; then \
		/usr/bin/install -c -m 0444 glMultMatrix.0.fixed \
		    /usr/X11R6/man/cat3/glMultMatrix.0; \
	fi
	cd xc/programs/rstart && ${MAKE} install CC="${CC}" \
	    && exec ${MAKE} install.man
	cd ${.CURDIR}/extras && exec ${MAKE} install
	/usr/libexec/makewhatis ${DESTDIR}/usr/X11R6/man
	chown root:wheel ${DESTDIR}/usr/X11R6/man/whatis.db

fix-appd:
	# Make sure ${LOCALAPPD} is a symbolic link
	if [[ ! -L ${DESTDIR}${LOCALAPPD} ]]; then \
		if [[ -d ${DESTDIR}${LOCALAPPD} ]]; then \
			mv ${DESTDIR}${LOCALAPPD}/* ${DESTDIR}${REALAPPD}/ \
			    || true; \
			rmdir ${DESTDIR}${LOCALAPPD}; \
		fi; \
		mkdir -p ${DESTDIR}${LOCALAPPX}; \
		ln -s ${REALAPPD} ${DESTDIR}${LOCALAPPD}; \
	fi

clean: ${_STFILE_SUB}
	cd xc && exec ${_STCMD_SUB} ${MAKE} clean

distclean:
	cd ${.CURDIR} && exec ${MAKE} clean
	sleep 1; rm -f ${_STFILE_SUB} xc/xmakefile

mrproper:
	[[ -h obj ]] || rm -rf *

perms:
.for _i in / /etc /etc/X11 /usr/X11R6 /usr/local /usr/local/lib \
    /usr/local/lib/X11
	chown ${DIROWN}:${DIRGRP} ${DESTDIR}${_i}/.
.endfor
	find ${DESTDIR}/etc/. ${DESTDIR}/usr/X11R6/. ${DESTDIR}/usr/local/. \
	    -type d \( \! -user ${DIROWN} -o \! -group ${DIRGRP} \) -ls \
	    | sed -e 's!/\./!/!'
	find ${DESTDIR}/etc/. ${DESTDIR}/usr/X11R6/. \
	    -type f \( \! -user ${BINOWN} -o \! -group wheel \) -ls \
	    | sed -e 's!/\./!/!'

dist:
	cd ${.CURDIR} && exec ${MAKE} perms
	@echo "============================================================"
	@echo "Checking files:"
	@echo ""
	cd ${BSDSRCDIR}/distrib/lists/x11 && MACHINE=${MACHINE} \
	    DESTDIR="${DESTDIR}" RELEASEDIR="${RELEASEDIR}" \
	    ${SHELL} ${BSDSRCDIR}/scripts/tarck
	@echo "============================================================"
.ifndef BATCH
	@read a?'Press Return to continue...'
.endif
	cd ${BSDSRCDIR}/distrib/lists/x11 && MACHINE=${MACHINE} \
	    DESTDIR="${DESTDIR}" RELEASEDIR="${RELEASEDIR}" \
	    ${SHELL} ${BSDSRCDIR}/scripts/tarmk ${OSrev}

release:
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} do-rel DESTDIR=${BSDRELDIR}/x11
	-cd ${RELEASEDIR}; cksum x*.ngz \
	    | cat - CKSUM | ${SUDO} sort -k3 -o CKSUM
	-cd ${RELEASEDIR}; rmd160 x*.ngz \
	    | cat - RMD160 | ${SUDO} sort -o RMD160

do-rel:
	mkdir -p ${DESTDIR} ${RELEASEDIR}
	${INSTALL} -d -o ${DIROWN} -g ${DIRGRP} -m ${DIRMODE} \
	    ${DESTDIR}/etc ${DESTDIR}/etc/X11 \
	    ${DESTDIR}/usr/X11R6 ${DESTDIR}/usr/X11R6/man/cat1 \
	    ${DESTDIR}/usr/local ${DESTDIR}/usr/local/lib/X11
	cd ${.CURDIR} && exec ${MAKE} install
.if (${MACHINE} == "macppc") || (${MACHINE} == "sparc")
	@if [[ -f ${DESTDIR}/etc/X11/XF86Config ]]; then \
		print Not overwriting existing ${DESTDIR}/etc/X11/XF86Config; \
	else \
		print ${INSTALL} ${INSTALL_COPY} -o root -g wheel -m 644 \
		    ${XCONFIG} ${DESTDIR}/etc/X11/XF86Config; \
		${INSTALL} ${INSTALL_COPY} -o root -g wheel -m 644 \
		    ${XCONFIG} ${DESTDIR}/etc/X11/XF86Config; \
	fi
.endif
	cd ${.CURDIR} && exec ${MAKE} fix-appd
	cd ${.CURDIR} && exec ${MAKE} dist

${_STFILE_SUB}: check-objdir
	cd ${SUBOBJDIR} && env WRITEDIR="${SUBOBJDIR}" \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}

check-objdir:
	@if [[ ! -e ${.CURDIR}/obj || -e Makefile || -d xc/Imakefile ]]; then \
		print "Error: you must make obj first."; \
		exit 1; \
	fi
	@if [[ ! -e xc ]]; then \
		mkdir -p xc; \
		(cd ${.OBJDIR}/xc && lndir ${.CURDIR}/xc); \
	fi

.PHONY: all b-r build check-objdir clean compile dist distclean \
	do-install do-rel fix-appd install mrproper perms release
