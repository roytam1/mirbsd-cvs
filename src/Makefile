# $MirOS: src/Makefile,v 1.28 2005/12/21 19:26:58 tg Exp $
# $OpenBSD: Makefile,v 1.103 2004/05/03 15:18:18 drahn Exp $

.include <bsd.own.mk>
.include "Makefile.inc"
NOMAN?=	no

  SUBDIR+= lib
  SUBDIR+= include
  SUBDIR+= bin
  SUBDIR+= libexec
  SUBDIR+= sbin
  SUBDIR+= usr.bin
  SUBDIR+= usr.sbin
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= share
  SUBDIR+= gnu
  SUBDIR+= sys
.endif
.if make(clean) || make(cleandir) || make(obj)
  SUBDIR+= distrib
.endif

includes:
	cd ${.CURDIR}/include && ${MAKE} prereq \
	    && exec ${SUDO} ${MAKE} includes

beforeinstall: distrib-dirs
	cd ${.CURDIR}/include && exec ${MAKE} includes

afterinstall:
.if ${NOMAN:L} == "no"
	cd ${.CURDIR}/share/man && exec ${MAKE} makedb
.endif
	-sleep 1; rm -f ${_STFILE_DEST}

mksystrace: mksystrace-obj mksystrace-dest

mksystrace-obj:
	cd ${BSDOBJDIR} && env WRITEDIR="${BSDOBJDIR}" \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}

mksystrace-dest:
	d="${DESTDIR}"; cd $${d:-/}; [[ -n $$d ]] || d="/:/*"; \
	    env WRITEDIR="$$d" NOWRITEDIR="${BSDOBJDIR}" \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}

build: mksystrace
	cd ${.CURDIR}/share/mk \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install
	cd ${.CURDIR}/include \
	    && ${_STCMD_OBJ} ${MAKE} prereq \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} includes
	cd ${.CURDIR} && ${SUDO} ${_STCMD_OBJ} ${MAKE} cleandir
	cd ${.CURDIR}/lib \
	    && ${_STCMD_OBJ} ${MAKE} depend \
	    && ${_STCMD_OBJ} ${MAKE} \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install NOMAN=yes
	cd ${.CURDIR} && ${_STCMD_OBJ} ${MAKE} depend
	# The build is now restartable from here.
	cd ${.CURDIR} && exec ${MAKE} contbuild

contbuild:
	[[ -s ${_STFILE_OBJ} ]] || ${MAKE} mksystrace-obj
	[[ -s ${_STFILE_DEST} ]] || ${MAKE} mksystrace-dest
	cd ${.CURDIR} && ${_STCMD_OBJ} ${MAKE} \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install
	-sleep 1; rm -f ${_STFILE_OBJ}

distrib-dirs:
	cd ${.CURDIR}/etc \
	    && exec ${SUDO} ${MAKE} distrib-dirs DESTDIR=${DESTDIR}

b-r: .PHONY
	# Test if the targets are mounted suitable for root (BTSTF)
.for _dir in ${BSDOBJDIR} ${BSDRELDIR}
	mkdir -p ${_dir} || ${SUDO} mkdir -p ${_dir}
	${SUDO} touch ${_dir}/permissions.test
	${SUDO} chown root:wheel ${_dir}/permissions.test
	${SUDO} rm ${_dir}/permissions.test
.endfor
	touch ${BSDOBJDIR}/permissions.test && rm ${BSDOBJDIR}/permissions.test
	cd ${.CURDIR} && exec ${MAKE} obj
	cd ${.CURDIR} && exec ${MAKE} build
	cd ${.CURDIR} && exec ${MAKE} contrelease

cont-b-r:
	cd ${.CURDIR} && exec ${MAKE} contbuild
	cd ${.CURDIR} && exec ${MAKE} contrelease

contrelease:
	@echo -n >/var/tmp/.buildnotice
	mkdir -p ${BSDRELDIR}/base ${BSDRELDIR}/rel \
	    || ${SUDO} mkdir -p ${BSDRELDIR}/base ${BSDRELDIR}/rel
	cd ${.CURDIR} && exec ${MAKE} mksystrace DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR}/etc && exec ${MAKE} release DESTDIR=${BSDRELDIR}/base
	-sleep 1; rm -f ${_STFILE_OBJ}

do-htman:
	-rm -rf ${BSDOBJDIR}/htman
	mkdir -p ${BSDOBJDIR}/htman/{man,htm}
.for _set _dir in x11 X11R6 base share
	cd ${BSDRELDIR}/${_set}/usr/${_dir}/man \
	    && find * -type f | cpio -pdlu ${BSDOBJDIR}/htman/man
.endfor
.for _doc in papers psd smm usd
	mkdir -p ${BSDOBJDIR}/htman/papers/${_doc}
	cd ${BSDOBJDIR}/htman/papers/${_doc} \
	    && lndir ${BSDRELDIR}/base/usr/share/doc/${_doc} \
	    && ${MAKE}
.endfor
	cp ${BSDOBJDIR}/share/doc/legal/LICENCE-BSD.0 \
	    ${BSDOBJDIR}/htman/man/cat7/BSD-Licence.0
	BSDOBJDIR="${BSDOBJDIR}" BSDSRCDIR="${BSDSRCDIR}" \
	    ${SHELL} ${.CURDIR}/scripts/genhtman.sh
	${SUDO} mkdir -p ${BSDRELDIR}/htman
	cd ${BSDOBJDIR}/htman/htm \
	    && find man* -type f | ${SUDO} cpio -pdlu ${BSDRELDIR}/htman/
	${SUDO} chown -R 0:0 ${BSDRELDIR}/htman/*
	${SUDO} chmod -R a=rX ${BSDRELDIR}/htman/*

dist-q:
	cd ${.CURDIR} && exec /usr/bin/env -i MAKEFLAGS=${MFLAGS:Q} \
	    HOME=$$(/usr/bin/mktemp -d /var/tmp/buildhome.XXXXXXXXXX) \
	    PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/X11R6/bin \
	    ${MAKE} BATCH=1 _do-dist 2>&1 | tee -a ${.CURDIR}/Build.log

dist:
	cd ${.CURDIR} && exec /usr/bin/env -i MAKEFLAGS=${MFLAGS:Q} \
	    HOME=$$(/usr/bin/mktemp -d /var/tmp/buildhome.XXXXXXXXXX) \
	    PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/X11R6/bin \
	    ${MAKE} _do-dist 2>&1 | tee -a ${.CURDIR}/Build.log

.ifdef QUICK_DIST
_DISTS=	base
.else
_DISTS=	base x11 htman
.endif

.ifdef QUICK_DIST
.  include "gcc/Makefile.lang"
.endif

_do-dist:
.ifdef QUICK_DIST
.  if ${NO_JAVA:L} == "no"
	@[[ -e /usr/X11R6/include/X11/X.h && -e /usr/X11R6/lib/libX11.a ]] \
	    || { print 'To build gcc/libjava you must have X11 installed!'; \
		 exit 1; }
.  endif
.endif
	mkdir -p ${HOME}/.etc/systrace
	@echo Initialising sudo as ${SUDO:Q}
	${SUDO} true
	@echo "============================================================"
	@echo Initiating MirOS Build...
	@date
.ifdef BATCH
	@echo BATCH mode engaged.
.else
	@echo INTERACTIVE mode engaged.
.endif
.ifdef QUICK_DIST
	@echo QUICK dist-build mode active:
	@echo not building XFree86® or HTML manual pages.
.endif
	@echo "============================================================"
	${SUDO} rm -rf ${BSDOBJDIR} ${BSDRELDIR}
	cd ${.CURDIR}/etc \
	    && exec ${SUDO} ${MAKE} distrib-dirs DESTDIR=
	cd ${.CURDIR} && exec ${MAKE} b-r
.ifndef QUICK_DIST
	@date
	cd ${.CURDIR}/X11 && exec ${MAKE} b-r
.endif
	@date
	cd ${.CURDIR}/gcc && exec ${MAKE} b-r
	cd ${.CURDIR}/gnu/usr.bin/perl && exec ${SUDO} ${MAKE} \
	    -f Makefile.bsd-wrapper DESTDIR=${BSDRELDIR}/base do-h2ph
	cd ${.CURDIR}/gnu/usr.bin/texinfo && exec ${SUDO} ${MAKE} \
	    -f Makefile.bsd-wrapper DESTDIR=${BSDRELDIR}/base mkinfodir
.ifndef QUICK_DIST
	@date
	cd ${.CURDIR} && exec ${MAKE} do-htman
.endif
	@date
	@echo "============================================================"
	@echo "Checking files:"
	@echo ""
.for _set in ${_DISTS}
	-cd ${BSDSRCDIR}/distrib/lists/${_set} && \
	    DESTDIR="${BSDRELDIR}/${_set}" RELEASEDIR="${BSDRELDIR}/rel" \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/tarck
.endfor
	@echo "============================================================"
.ifndef BATCH
	@read a?'Press Return to continue...'
.endif
.for _set in ${_DISTS}
	-cd ${BSDSRCDIR}/distrib/lists/${_set} && \
	    DESTDIR="${BSDRELDIR}/${_set}" RELEASEDIR="${BSDRELDIR}/rel" \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/tarmk ${OSrev}
.endfor
	-cd ${BSDRELDIR}/rel && cksum bsd!(*.gz) *boot* *BOOT* *.fs \
	    *.iso *.gz *.ngz | cat - CKSUM | ${SUDO} sort -k3 -uo CKSUM
	-cd ${BSDRELDIR}/rel && rmd160 bsd!(*.gz) *boot* *BOOT* *.fs \
	    *.iso *.gz *.ngz | cat - RMD160 | ${SUDO} sort -uo RMD160
	-cd ${BSDRELDIR}/rel && for f in RMD160.asc index.txt *; do \
		print "$$f"; \
	 done | ${SUDO} sort -uo index.txt
	@echo "============================================================"
	@echo Done with MirOS Build.
	@date
	@/bin/ls -Fl ${BSDRELDIR}/rel
	@echo "============================================================"
	@echo 'You might want to nuke ${HOME} now...'

CVSROOT?=/cvs
cvsup:
	cd ${.CURDIR} && cvs -Rqz3 -d ${CVSROOT} up -PAd [!BCXcptw]!(*cc) .*

.PHONY:	includes beforeinstall afterinstall mksystrace mksystrace-obj \
	mksystrace-dest build contbuild distrib-dirs b-r contrelease \
	cont-b-r cvsup do-htman dist dist-q _do-dist

.include <bsd.subdir.mk>

cleandir:
	-rm -rf ${BSDOBJDIR}/htman
