# $MirOS: X11/Makefile,v 1.1 2005/03/19 13:21:35 tg Exp $

.include <bsd.own.mk>
.include "${BSDSRCDIR}/Makefile.inc"

SUBOBJDIR!=	readlink ${.OBJDIR} || ( cd ${.OBJDIR} && pwd )

.if ${MACHINE} == i386
XMACH=		ix86
.else
XMACH=		${MACHINE}
.endif
BINDIST=	programs/Xserver/hw/xfree86/etc/bindist
HOSTDEF=	xc/${BINDIST}/OpenBSD-${XMACH}/host.def
CONFHOSTDEF=	xc/config/cf/host.def
XCONFIG=	xc/${BINDIST}/OpenBSD-${XMACH}/XF86Config

DIROWN?=	root
DIRGRP?=	wheel

LOCALAPPD=	/usr/local/lib/X11/app-defaults
LOCALAPPX=	/usr/local/lib/X11
REALAPPD=	/etc/X11/app-defaults


all: ${_STFILE_SUB}
	cd ${.CURDIR} && ${_STCMD_SUB} ${MAKE} compile

obj:
	@cd ${.CURDIR}; \
	here=$$(/bin/pwd); bsdsrcdir=$$(cd ${BSDSRCDIR}; /bin/pwd); \
	bsdobjdir=$$(cd ${BSDOBJDIR}; /bin/pwd); \
	subdir=$${here#$${bsdsrcdir}/}; \
	dest=$${bsdobjdir}/$$subdir; \
	echo "linking $$here -> $$dest"; \
	if test -d $${bsdobjdir} -a ! -d $$dest; then \
		mkdir -p $$dest; \
		( cd $$dest; lndir $$here ); \
	else \
		true; \
	fi;

compile:
	rm -f ${CONFHOSTDEF}
	${INSTALL} ${HOSTDEF} ${CONFHOSTDEF}
.if ${MKC_USAP:L} != "yes"
	echo '#define Freetype2BuildDefines	'\
		'-DTT_CONFIG_OPTION_BYTECODE_INTERPRETER' >>${CONFHOSTDEF}
.endif
.if defined(NOFONTS)
	echo "#define BuildFonts		NO" >>${CONFHOSTDEF}
.endif
	cd ${.CURDIR}/xc && exec ${MAKE} World \
	    WORLDOPTS="CC=${CC:Q} CXX=${CXX:Q} COPTS=${COPTS:Q}" \
	    CC="${CC}" CXX="${CXX}" COPTS="${COPTS}"
	cd ${.CURDIR}/extras && ${MAKE} obj && ${MAKE} depend && exec ${MAKE}

build:
	cd ${.CURDIR} && ${MAKE} compile
	cd ${.CURDIR} && ${SUDO} ${MAKE} install
	cd ${.CURDIR} && ${SUDO} ${MAKE} fix-appd

release: release-clean release-mkdir release-install fix-appd dist

release-clean:
.if ! ( defined(DESTDIR) && defined(RELEASEDIR) )
	@echo You must set DESTDIR and RELEASEDIR for a release.; exit 255
.endif
	rm -rf ${DESTDIR}/usr/X11R6/* ${DESTDIR}/usr/X11R6/.[a-zA-Z0-9]*
	rm -rf ${DESTDIR}/var/X11/*
	rm -rf ${DESTDIR}/etc/X11/*
	rm -rf ${DESTDIR}/etc/fonts/*
	@if [ -d ${DESTDIR}/usr/X11R6 ] && [ "$$(cd ${DESTDIR}/usr/X11R6;ls)" ]; then \
		echo "Files found in ${DESTDIR}/usr/X11R6:"; \
		(cd ${DESTDIR}/usr/X11R6;/bin/pwd;ls -a); \
		echo "Cleanup before proceeding."; \
		exit 255; \
	fi

release-mkdir:
	@${INSTALL} -d -o ${DIROWN} -g ${DIRGRP} -m ${DIRMODE} \
		${DESTDIR}/usr/X11R6 ${DESTDIR}/etc/X11 \
		${DESTDIR}/usr/local/lib/X11 \
		${DESTDIR}/usr/X11R6/man \
		${DESTDIR}/usr/X11R6/man/cat1
	@cd ${.CURDIR} && ${MAKE} perms

release-install:
	@cd ${.CURDIR} && ${MAKE} install
.if ${MACHINE} == "macppc" || ${MACHINE} == "sparc"
	@if [[ -f $(DESTDIR)/etc/X11/XF86Config ]]; then \
		echo "Not overwriting existing $(DESTDIR)/etc/X11/XF86Config"; \
	  else \
		set -x; \
		${INSTALL} ${INSTALL_COPY} -o root -g wheel -m 644 \
		    ${XCONFIG} ${DESTDIR}/etc/X11/XF86Config; \
	fi
.endif
	@cd ${.CURDIR} && ${MAKE} fix-appd

PERMDIRS=	/ /usr /usr/X11R6 /etc /etc/X11 /usr/local \
		/usr/local/lib /usr/local/lib/X11
perms:
.for _dir in ${PERMDIRS}
	chown ${DIROWN}:${DIRGRP} ${DESTDIR}${_dir}/.
.endfor
	find ${DESTDIR}/usr/X11R6/. ${DESTDIR}/etc/. ${DESTDIR}/usr/local/. \
		-type d \
		\( \! -user ${DIROWN} -o \! -group ${DIRGRP} \) \
		-ls
	find ${DESTDIR}/usr/X11R6/. ${DESTDIR}/etc/. \
		-type f \
		\( \! -user ${BINOWN} -o \! -group wheel \) \
		-ls

dist:
	cd ${.CURDIR} && ${MAKE} perms
	@echo "============================================================"
	@echo "Checking files:"
	@echo ""
	cd ${BSDSRCDIR}/distrib/lists/x11 && MACHINE=${MACHINE} \
	    ${SHELL} ${BSDSRCDIR}/scripts/checkflist
	@echo "============================================================"
.ifdef WAIT_CHECKFLIST
	@read a?'Press Return to continue...'
.endif
	cd ${BSDSRCDIR}/distrib/lists/x11 && MACHINE=${MACHINE} \
	    ${SHELL} ${BSDSRCDIR}/scripts/maketars ${OSrev}

install: install-xc install-extra
	/usr/libexec/makewhatis ${DESTDIR}/usr/X11R6/man
	chown root:wheel ${DESTDIR}/usr/X11R6/man/whatis.db

install-xc:
	d="${DESTDIR}"; cd $${d:-/}; [[ -n $$d ]] || d="/:/*"; \
	    env WRITEDIR="$$d" NOWRITEDIR="${SUBOBJDIR}" ${EXTRA_ENV} \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk make
	cd ${.CURDIR}/xc \
	    && ${_STCMD_DEST} ${MAKE} install CC="${CC}" \
	    && ${_STCMD_DEST} ${MAKE} install.man
	cd ${.CURDIR}/xc/programs/rstart \
	    && ${_STCMD_DEST} ${MAKE} install \
	    && ${_STCMD_DEST} ${MAKE} install.man
	sleep 1; rm -f ${_STFILE_DEST}

install-extra:
	cd ${.CURDIR}/extras && exec ${MAKE} install

fix-appd:
	# Make sure /usr/local/lib/X11/app-defaults is a link
	if [[ ! -L $(DESTDIR)${LOCALAPPD} ]]; then \
	    if [[ -d $(DESTDIR)${LOCALAPPD} ]]; then \
		mv $(DESTDIR)${LOCALAPPD}/* $(DESTDIR)${REALAPPD} || true; \
		rmdir $(DESTDIR)${LOCALAPPD}; \
	    fi; \
	    mkdir -p ${DESTDIR}${LOCALAPPX}; \
	    ln -s ${REALAPPD} ${DESTDIR}${LOCALAPPD}; \
	fi

clean: ${_STFILE_SUB}
	cd ${.CURDIR}/xc && ${_STCMD_SUB} ${MAKE} clean

distclean:
	cd ${.CURDIR} && ${MAKE} clean
	@sleep 1
	rm -f xc/xmakefile ${_STFILE_SUB}

b-r:
	@echo ${SHELL} ${.CURDIR}/build-release
	@exec ${SHELL} ${.CURDIR}/build-release

.PHONY:	all build release dist install install-xc install-extra clean \
	distclean fix-appd b-r release-clean release-mkdir release-install
