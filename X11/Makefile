# $MirOS: X11/Makefile,v 1.38 2008/10/05 16:26:12 tg Exp $

.include <bsd.own.mk>
.include "${BSDSRCDIR}/Makefile.inc"

SUBOBJDIR!=	realpath ${.OBJDIR}
BINDIST=	programs/Xserver/hw/xfree86/etc/bindist
HOSTDEF=	xc/${BINDIST}/OpenBSD-${MACHINE}/host.def
CONFHOSTDEF=	xc/config/cf/host.def
XCONFIG=	xc/${BINDIST}/OpenBSD-${MACHINE}/XF86Config
LOCALAPPX=	/usr/local/lib/X11
LOCALAPPD=	${LOCALAPPX}/app-defaults
REALAPPD=	/etc/X11/app-defaults
WORLD=		World

.include <bsd.obj.mk>

.if make(obj)
  SUBDIR+=	depends
  SUBDIR+=	extras
.  include <bsd.subdir.mk>
.endif

.MAIN: all
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
	cd ${.CURDIR} && ${MAKE} obj && exec ${MAKE} check-objdir
	cd ${.CURDIR} && exec ${MAKE} build

compile:
	${INSTALL} -d -m ${DIRMODE} \
	    ${SUBOBJDIR}/xc/exports/bin \
	    ${SUBOBJDIR}/xc/exports/include \
	    ${SUBOBJDIR}/xc/exports/include/{DPS,GL,X11,fontconfig,freetype2} \
	    ${SUBOBJDIR}/xc/exports/lib \
	    ${SUBOBJDIR}/xc/exports/lib/{X11,modules,pkgconfig} \
	    ${SUBOBJDIR}/xc/exports/man \
	    ${SUBOBJDIR}/xc/exports/man/cat{1,3,4,5,7}
	cd ${.CURDIR}/extras/bdfctool && ${MAKE} depend && ${MAKE}
	cd ${.CURDIR}/depends && ${MAKE} depend && ${MAKE} && \
	    exec ${SUDO} ${MAKE} install X11BASE=${SUBOBJDIR}/xc/exports
	${SUDO} chown -R $$(id -u) ${SUBOBJDIR}/xc/exports
	cd ${SUBOBJDIR}/xc/exports/include/freetype2/freetype; \
	    ln -sf ${SUBOBJDIR}/xc/extras/freetype2/include/freetype/internal
	rm -f ${CONFHOSTDEF}
	${INSTALL} ${HOSTDEF} ${CONFHOSTDEF}
.if defined(NOFONTS) && ${NOFONTS:L} != "no"
	echo "#define BuildFonts		NO" >>${CONFHOSTDEF}
.endif
	cd xc && exec env PATH=${SUBOBJDIR:Q}/extras/bdfctool:$$PATH \
	    ${MAKE} ${WORLD} WORLDOPTS="CC=${CC:Q} CXX=${CXX:Q} \
	    COPTS=${COPTS:Q} CPPFLAGS=${CPPFLAGS:Q}" \
	    CC="${CC}" CXX="${CXX}" COPTS="${COPTS}" CPPFLAGS="${CPPFLAGS}"
	cd ${.CURDIR}/extras/bdfctool && ${MAKE} cleandir
	cd ${.CURDIR}/extras && ${MAKE} depend && exec ${MAKE}

install:
	d="${DESTDIR}"; cd $${d:-/}; [[ -n $$d ]] || d="/:/*"; \
	    env WRITEDIR="$$d" NOWRITEDIR="${SUBOBJDIR}" ${EXTRA_ENV} \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}
	cd ${.CURDIR} && exec ${_STCMD_DEST} ${MAKE} do-install
	sleep 1; rm ${_STFILE_DEST}

do-install:
	${INSTALL} -d -o 0 -g 0 -m ${DIRMODE} \
	    ${DESTDIR}/usr/X11R6/bin \
	    ${DESTDIR}/usr/X11R6/include \
	    ${DESTDIR}/usr/X11R6/include/{DPS,GL,X11,fontconfig,freetype2} \
	    ${DESTDIR}/usr/X11R6/lib \
	    ${DESTDIR}/usr/X11R6/lib/{X11,modules,pkgconfig} \
	    ${DESTDIR}/usr/X11R6/man \
	    ${DESTDIR}/usr/X11R6/man/cat{1,3,4,5,7}
	cd ${.CURDIR}/depends && exec ${MAKE} install
	cd xc && env PATH=${SUBOBJDIR:Q}/extras/bdfctool:$$PATH \
	    ${MAKE} install CC="${CC}" && \
	    exec env PATH=${SUBOBJDIR:Q}/extras/bdfctool:$$PATH \
	    ${MAKE} install.man
	cd ${.CURDIR}/extras && exec ${MAKE} install
	/usr/libexec/makewhatis ${DESTDIR}/usr/X11R6/man
.if !defined(NOFONTS) || ${NOFONTS:L} == "no"
	LD_LIBRARY_PATH=${DESTDIR}/usr/X11R6/lib:${DESTDIR}/usr/lib \
	    ${DESTDIR}/usr/X11R6/bin/fc-cache -v \
	    ${DESTDIR}/usr/X11R6/lib/X11/fonts
.endif
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
		ln -sf ${REALAPPD} ${DESTDIR}${LOCALAPPD}; \
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
	chown 0:0 ${DESTDIR}${_i}/.
.endfor
	find ${DESTDIR}/etc/. ${DESTDIR}/usr/X11R6/. ${DESTDIR}/usr/local/. \
	    -type d \( \! -user 0 -o \! -group 0 \) -ls \
	    | sed -e 's!/\./!/!'
	find ${DESTDIR}/etc/. ${DESTDIR}/usr/X11R6/. \
	    -type f \( \! -user 0 -o \! -group 0 \) -ls \
	    | sed -e 's!/\./!/!'

dist:
	cd ${.CURDIR} && exec ${MAKE} perms

release:
	mkdir -p ${DESTDIR} ${BSDRELDIR}/rel
	${INSTALL} -d -o 0 -g 0 -m ${DIRMODE} \
	    ${DESTDIR}/etc ${DESTDIR}/etc/X11 \
	    ${DESTDIR}/usr/local ${DESTDIR}/usr/local/lib/X11
	cd ${.CURDIR} && exec ${MAKE} install
.if exists(${XCONFIG})
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
	do-install fix-appd install mrproper perms release
