# $MirOS: src/Makefile,v 1.8 2005/03/29 12:24:56 tg Exp $
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
	${SUDO} ${_STCMD_OBJ} ${MAKE} cleandir
	cd ${.CURDIR}/lib \
	    && ${_STCMD_OBJ} ${MAKE} depend \
	    && ${_STCMD_OBJ} ${MAKE} \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install NOMAN=yes
	${_STCMD_OBJ} ${MAKE} depend
	# The build is now restartable from here.
	exec ${MAKE} contbuild

contbuild:
	[[ -s ${_STFILE_OBJ} ]] || ${MAKE} mksystrace-obj
	[[ -s ${_STFILE_DEST} ]] || ${MAKE} mksystrace-dest
	${_STCMD_OBJ} ${MAKE} \
	    && ${SUDO} ${_STCMD_DEST} ${MAKE} install
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
	@echo ============================================================
	@date
	@echo ============================================================
	${MAKE} obj
	${MAKE} build
	${MAKE} contrelease BSDRELDIR=${BSDRELDIR}

contrelease:
	@echo -n >/var/tmp/.buildnotice
	mkdir -p ${BSDRELDIR}/base ${BSDRELDIR}/rel \
	    || ${SUDO} mkdir -p ${BSDRELDIR}/base ${BSDRELDIR}/rel
	cd ${.CURDIR} && ${MAKE} mksystrace DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR}/etc && exec ${MAKE} \
	    release DESTDIR=${BSDRELDIR}/base RELEASEDIR=${BSDRELDIR}/rel
	-sleep 1; rm -f ${_STFILE_OBJ}
	@echo ============================================================
	@echo Build and Release for the MirOS base system complete.
	@date; uname -a
	@echo ============================================================

do-htman:
	mkdir -p ${BSDOBJDIR}/htman/{man,htm}
.for _i in x11 gcc base
	cd ${BSDRELDIR}/${_i}/usr/share/man \
	    && find * -type f | cpio -pdlu ${BSDOBJDIR}/htman/man
.endfor
.for _i in papers psd smm usd
	mkdir -p ${BSDOBJDIR}/htman/papers/${_i}
	cd ${BSDOBJDIR}/htman/papers/${_i} \
	    && lndir ${BSDOBJDIR}/base/usr/share/doc/${_i} \
	    && ${MAKE}
.endfor
	BSDOBJDIR="${BSDOBJDIR}" BSDRELDIR="${BSDRELDIR}" \
	    BSDSRCDIR="${BSDSRCDIR}" SUDO="${SUDO}" OSrev="${OSrev}" \
	    ${SHELL} ${.CURDIR}/scripts/genhtman.sh
	${SUDO} mkdir -p ${BSDRELDIR}/htman
	cd ${BSDOBJDIR}/htman/htm \
	    && find man* -name \*.htm | ${SUDO} cpio -pdlu ${BSDRELDIR}/htman
	${SUDO} chown -R 0:0 ${BSDRELDIR}/htman/*
	${SUDO} chmod -R a=rX ${BSDRELDIR}/htman/*
	@echo "============================================================"
	@echo "Checking files:"
	@echo ""
	-cd ${BSDSRCDIR}/distrib/lists/htman && DESTDIR=${BSDRELDIR}/htman \
	    RELEASEDIR=${BSDRELDIR}/rel ${EXTRA_ENV} ${SUDO} ${SHELL} \
	    ${BSDSRCDIR}/scripts/tarck
	@echo "============================================================"
.ifndef BATCH
	@read a?'Press Return to continue...'
.endif
	cd ${BSDSRCDIR}/distrib/lists/htman && DESTDIR=${BSDRELDIR}/htman \
	    RELEASEDIR=${BSDRELDIR}/rel ${EXTRA_ENV} ${SUDO} ${SHELL} \
	    ${BSDSRCDIR}/scripts/tarmk ${OSrev}
	-cd ${BSDRELDIR}/rel; cksum htman*.ngz \
	    | cat - CKSUM | ${SUDO} sort -k3 -o CKSUM
	-cd ${BSDRELDIR}/rel; rmd160 htman*.ngz \
	    | cat - RMD160 | ${SUDO} sort -o RMD160
	@echo ============================================================
	@echo Build and Release for the HTML Documentation complete.
	@date; uname -a
	@echo ============================================================

dist-q:
	cd ${.CURDIR} && exec ${MAKE} dist BATCH=defined

dist:
	@echo Initiating MirOS Build...
	@date
.ifdef BATCH
	@echo BATCH mode engaged.
.else
	@echo INTERACTIVE mode engaged.
.endif
	${SUDO} rm -rf ${BSDOBJDIR} ${BSDRELDIR}
	cd ${.CURDIR}/etc \
	    && exec ${SUDO} ${MAKE} distrib-dirs DESTDIR=
	cd ${.CURDIR} && exec ${MAKE} b-r
	cd ${.CURDIR}/X11 && exec ${MAKE} b-r
	cd ${.CURDIR}/gcc && exec ${MAKE} b-r
	cd ${.CURDIR} && exec ${MAKE} do-htman
	@echo Done with MirOS Build.
	@date
	@/bin/ls -Fl ${BSDRELDIR}/rel

CVSROOT?=/cvs
cvsup:
	-rm -f ${.CURDIR}/Build.log
	cd ${.CURDIR} && cvs -Rqz3 -d ${CVSROOT} up -PAd [!CXcptw]!(*cc) .*

.PHONY:	includes beforeinstall afterinstall mksystrace mksystrace-obj \
	mksystrace-dest build contbuild distrib-dirs b-r contrelease \
	cvsup do-htman dist dist-q

.include <bsd.subdir.mk>
