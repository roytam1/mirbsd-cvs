# $MirOS: src/Makefile,v 1.40 2006/04/10 21:26:29 tg Exp $
# $OpenBSD: Makefile,v 1.103 2004/05/03 15:18:18 drahn Exp $

.if defined(MAKECONF) && exists(${MAKECONF})
.  error MAKECONF is set to '${MAKECONF}', you don't want this!
.endif
.include <bsd.own.mk>
.include "Makefile.inc"
NOMAN?=	no
CVSROOT?=/cvs

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

beforeinstall: distrib-dirs
	cd ${.CURDIR}/include && exec ${MAKE} includes

afterinstall:
.if ${NOMAN:L} == "no"
	cd ${.CURDIR}/share/man && exec ${MAKE} makedb
.endif

mksystrace: mksystrace-obj mksystrace-dest

mksystrace-obj:
	cd ${BSDOBJDIR} && env WRITEDIR="${BSDOBJDIR}" \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}

mksystrace-dest:
	d="${DESTDIR}"; cd $${d:-/}; [[ -n $$d ]] || d="/:/*"; \
	    env WRITEDIR="$$d" NOWRITEDIR="${BSDOBJDIR}" \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}

build-pre:
	-${SUDO} rm -f ${_STFILE_OBJ} ${_STFILE_DEST}
	cd ${.CURDIR} && exec ${MAKE} mksystrace
	cd ${.CURDIR}/share/mk \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install
	cd ${.CURDIR}/include \
	    && ${_STCMD_OBJ} ${MAKE} prereq \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} includes
	rm -rf ${BSDOBJDIR}/{lib,sys}
	cd ${.CURDIR}/lib && ${MAKE} obj
	cd ${.CURDIR}/sys && ${MAKE} obj
	cd ${.CURDIR}/lib \
	    && ${_STCMD_OBJ} ${MAKE} depend \
	    && ${_STCMD_OBJ} ${MAKE} \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install NOMAN=yes
	cd ${.CURDIR} && ${_STCMD_OBJ} ${MAKE} depend

contbuild:
	cd ${.CURDIR} && exec ${MAKE} mksystrace
	cd ${.CURDIR} && ${_STCMD_OBJ} ${MAKE} \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install
	@sleep 1
	${SUDO} rm -f ${_STFILE_OBJ} ${_STFILE_DEST}

distrib-dirs:
	[[ -d ${DESTDIR}/. ]] || \
	    ${SUDO} ${INSTALL} -d -o root -g wheel -m 755 ${DESTDIR}
	${SUDO} mtree -p ${DESTDIR}/ -Uqdef ${.CURDIR}/etc/mtree/4.4BSD.dist
	cd ${DESTDIR}/var/anoncvs/anoncvs && \
	    ${SUDO} rm -f usr var && \
	    ${SUDO} ln -s . var
	for i in ${DESTDIR}/usr/{ports,src}; do \
		[[ -d $$i ]] || \
		    ${SUDO} ${INSTALL} -d -o root -g wsrc -m 775 $$i; \
	done
	cd ${DESTDIR}/ && ${SUDO} rm -f sys && ${SUDO} ln -s usr/src/sys sys

b-r:
	# Test if the targets are mounted suitable for root (BTSTF)
.for _dir in ${BSDOBJDIR} ${BSDRELDIR}
	mkdir -p ${_dir} || ${SUDO} mkdir -p ${_dir}
	${SUDO} touch ${_dir}/permissions.test
	${SUDO} chown root:wheel ${_dir}/permissions.test
	${SUDO} rm ${_dir}/permissions.test
.endfor
	touch ${BSDOBJDIR}/permissions.test && rm ${BSDOBJDIR}/permissions.test
	cd ${.CURDIR} && exec ${MAKE} obj
	cd ${.CURDIR} && exec ${MAKE} build-pre DESTDIR=
	cd ${.CURDIR} && exec ${MAKE} contbuild DESTDIR=
	cd ${.CURDIR} && exec ${MAKE} contrelease DESTDIR=${BSDRELDIR}/base

cont-b-r:
	cd ${.CURDIR} && exec ${MAKE} contbuild DESTDIR=
	cd ${.CURDIR} && exec ${MAKE} contrelease DESTDIR=${BSDRELDIR}/base

contrelease:
	mkdir -p ${DESTDIR} || ${SUDO} mkdir -p ${DESTDIR}
	cd ${.CURDIR} && exec ${MAKE} mksystrace-dest
	cd ${.CURDIR} && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install
	cd ${.CURDIR}/etc && exec ${SUDO} ${_STCMD_DEST} ${MAKE} etc-files
	@sleep 1
	${SUDO} rm -f ${_STFILE_DEST}

do-htman:
	-rm -rf ${BSDOBJDIR}/htman
	mkdir -p ${BSDOBJDIR}/htman/{man,htm}
	cd ${BSDOBJDIR}/htman && env WRITEDIR="${BSDOBJDIR}/htman" \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE} ${SHELL}
.for _set _dir in x11 X11R6 base share
	cd ${BSDRELDIR}/${_set}/usr/${_dir}/man \
	    && find * -type f | cpio -pdlu ${BSDOBJDIR}/htman/man
.endfor
.for _doc in papers psd smm usd
	mkdir -p ${BSDOBJDIR}/htman/papers/${_doc}
	cd ${BSDOBJDIR}/htman/papers/${_doc} \
	    && lndir ${BSDRELDIR}/base/usr/share/doc/${_doc} \
	    && ${_STCMD} -f ${BSDOBJDIR}/htman/.policy.mk ${MAKE}
.endfor
	cp ${BSDOBJDIR}/share/doc/legal/LICENCE-BSD.0 \
	    ${BSDOBJDIR}/htman/man/cat7/BSD-Licence.0
	BSDOBJDIR="${BSDOBJDIR}" BSDSRCDIR="${BSDSRCDIR}" \
	    ${_STCMD} -f ${BSDOBJDIR}/htman/.policy.mk \
	    ${SHELL} ${.CURDIR}/scripts/genhtman.sh
	-rm -f ${BSDOBJDIR}/htman/.policy.mk
	${SUDO} mkdir -p ${BSDRELDIR}/htman
	cd ${BSDOBJDIR}/htman/htm \
	    && find man* -type f | ${SUDO} cpio -pdlu ${BSDRELDIR}/htman/
	${SUDO} chown -R 0:0 ${BSDRELDIR}/htman/*
	${SUDO} chmod -R a=rX ${BSDRELDIR}/htman/*

base-distbuild:
	cd ${.CURDIR} && exec ${MAKE} mksystrace-obj
	cd ${.CURDIR}/distrib && exec ${_STCMD_OBJ} ${MAKE}
	-rm -f ${_STFILE_OBJ}

base-distinstall:
	cd ${.CURDIR} && exec ${MAKE} mksystrace-dest
	-rm -rf ${_STFILE_OBJ} ${DESTDIR}/snapshot
	${INSTALL} -d -o root -g wheel -m 755 ${DESTDIR}/snapshot
	cd ${.CURDIR}/distrib && exec ${_STCMD_DEST} ${MAKE} install
	cd ${.CURDIR}/etc && exec ${_STCMD_DEST} ${MAKE} snap_md
	cd ${.CURDIR}/gnu/usr.bin/texinfo && exec ${_STCMD_DEST} \
	    ${MAKE} -f Makefile.bsd-wrapper mkinfodir
	-rm -f ${_STFILE_DEST}

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

_INDEX_FILES=	CKSUM RMD160 RMD160.gz source${OSrev}.ngz xfree${OSrev}.ngz

.ifdef QUICK_DIST
.  include "gcc/Makefile.lang"
.endif

_do-dist:
	@h=${HOME:Q}; [[ $$h = $$HOME ]] || exit 1
	@if [[ $$HOME != /var/tmp/buildhome.* ]]; then \
		echo Do not call this target directly; \
		exit 1; \
	fi
	mkdir -p ${HOME}/.etc/systrace
.ifdef QUICK_DIST
.  if ${NO_JAVA:L} == "no"
	@[[ -e /usr/X11R6/include/X11/X.h && -e /usr/X11R6/lib/libX11.a ]] \
	    || { print 'To build gcc/libjava you must have X11 installed!'; \
		 ${SUDO} rm -rf ${HOME}; \
		 exit 1; }
.  endif
.endif
	@echo Initialising sudo as ${SUDO:Q}
	${SUDO} true
	@if [[ -e /var/tmp/.buildnotice ]]; then \
		echo Error: /var/tmp/.buildnotice existed.; \
		${SUDO} cat /var/tmp/.buildnotice; \
		${SUDO} rm -rf ${HOME}; \
		exit 1; \
	fi
	@echo "============================================================"
	@echo Initiating MirOS Build...
	${SUDO} install -c -o 0 -g 0 -m 600 /dev/null /var/tmp/.buildnotice
	${SUDO} mksh -c 'echo rm -rf ${HOME} >>/var/tmp/.buildnotice'
	@date
.ifdef BATCH
	@echo BATCH mode engaged.
.else
	@echo INTERACTIVE mode engaged.
.endif
.ifdef QUICK_DIST
	@echo QUICK dist-build mode active:
	@echo not building XFree86®, ports or HTML manual pages.
.endif
	@echo "============================================================"
	${SUDO} rm -rf ${BSDOBJDIR} ${BSDRELDIR}
	cd ${.CURDIR} && exec ${MAKE} distrib-dirs DESTDIR=
	cd ${.CURDIR} && exec ${MAKE} b-r
.ifndef QUICK_DIST
	@date
	cd ${.CURDIR}/X11 && exec ${MAKE} b-r
.endif
	@date
	cd ${.CURDIR}/gcc && exec ${MAKE} b-r
	@date
	cd ${.CURDIR} && exec ${MAKE} base-distbuild DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} base-distinstall \
	    DESTDIR=${BSDRELDIR}/base
.ifndef QUICK_DIST
	@date
	cd ${.CURDIR} && exec ${MAKE} do-htman
.endif
	${SUDO} rm -rf ${BSDRELDIR}/rel
	mkdir ${BSDRELDIR}/rel
.ifndef QUICK_DIST
	@date
	SUDO=${SUDO:Q} OSrev=${OSrev:Q} BSDRELDIR=${BSDRELDIR:Q} \
	    CVSROOT=${CVSROOT:Q} ${MKSH} ${BSDSRCDIR}/scripts/tarports
.endif
	@date
	@echo "============================================================"
	@if [[ -e /var/tmp/.buildnotice ]]; then \
		${SUDO} cat /var/tmp/.buildnotice; \
		${SUDO} /bin/mksh /var/tmp/.buildnotice; \
		${SUDO} rm -f /var/tmp/.buildnotice || true; \
		echo "============================================================"; \
	fi
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
	cd ${BSDRELDIR}/base/snapshot && ${SUDO} ${INSTALL} -c \
	    -o root -g wheel -m 444 * ${BSDRELDIR}/rel/
.for _set in ${_DISTS}
	-cd ${BSDSRCDIR}/distrib/lists/${_set} && \
	    DESTDIR="${BSDRELDIR}/${_set}" RELEASEDIR="${BSDRELDIR}/rel" \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/tarmk ${OSrev}
.endfor
	-cd ${BSDRELDIR}/rel && ${SUDO} touch ${_INDEX_FILES} index.txt
	-cd ${BSDRELDIR}/rel && /bin/ls -1 | ${SUDO} sort -uo index.txt
	-cd ${BSDRELDIR}/rel && ${SUDO} rm -f ${_INDEX_FILES}
.for _i in ${_INDEX_FILES:M*.ngz}
	test ! -e ${BSDSRCDIR}/${_i} || \
	    ${SUDO} ln -s ${BSDSRCDIR}/${_i} ${BSDRELDIR}/rel/
.endfor
	-cd ${BSDRELDIR}/rel && cksum * | ${SUDO} sort -k3 -uo CKSUM
	-cd ${BSDRELDIR}/rel && rmd160 !(CKSUM) | ${SUDO} sort -uo RMD160
	-gzip -n9 <${BSDRELDIR}/rel/RMD160 >${HOME}/RMD160.gz
	# pad for gzsig(1) application later on
	-dd if=/dev/zero bs=768 count=1 >>${HOME}/RMD160.gz
	-${SUDO} mv ${HOME}/RMD160.gz ${BSDRELDIR}/rel/
	@echo "============================================================"
	@echo Done with MirOS Build.
	@date
	@/bin/ls -Fl ${BSDRELDIR}/rel
	@echo "============================================================"
.if ${MACHINE_ARCH} == "i386"
	cd ${BSDSRCDIR}/distrib/i386/livecd && ${MAKE} it
	@echo
	@echo Done with MirOS Snapshot generation.
	@date
	@/bin/ls -Fl ${BSDOBJDIR}/distrib/i386/livecd/livecd${OSrev}.iso
	@echo "============================================================"
.endif

cvsup:
	cd ${.CURDIR} && cvs -Rqz3 -d ${CVSROOT} up -PAd [!BCXcptw]!(*cc) .*

.PHONY:	beforeinstall afterinstall mksystrace mksystrace-obj mksystrace-dest \
	build-pre contbuild distrib-dirs b-r cont-b-r contrelease do-htman \
	base-distbuild base-distinstall dist-q dist _do-dist cvsup cleandir

.include <bsd.subdir.mk>

cleandir:
	-rm -rf ${BSDOBJDIR}/htman
