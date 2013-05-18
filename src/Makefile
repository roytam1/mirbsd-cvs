# $MirOS: src/Makefile,v 1.88 2006/12/20 15:56:46 tg Exp $
# $OpenBSD: Makefile,v 1.103 2004/05/03 15:18:18 drahn Exp $

.if defined(MAKECONF) && exists(${MAKECONF})
.  error MAKECONF is set to '${MAKECONF}', you don't want this!
.endif
.include <bsd.own.mk>
.include "Makefile.inc"
NOMAN?=		no
CVSROOT?=	/cvs
ANONCVSROOT?=	anoncvs@anoncvs.mirbsd.org:/cvs

  SUBDIR+= lib
  SUBDIR+= include
  SUBDIR+= bin
  SUBDIR+= libexec
  SUBDIR+= sbin
  SUBDIR+= usr.bin
  SUBDIR+= usr.sbin
  SUBDIR+= share
  SUBDIR+= gnu
  SUBDIR+= sys
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
	cd ${BSDOBJDIR} && env WRITEDIR=${BSDOBJDIR:Q} \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}

mksystrace-dest:
	d=${DESTDIR:Q}; cd $${d:-/}; [[ -n $$d ]] || d="/:/*"; \
	    env WRITEDIR="$$d" NOWRITEDIR=${BSDOBJDIR:Q} \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE}

build-pre:
	-${SUDO} rm -f ${_STFILE_OBJ} ${_STFILE_DEST}
	cd ${.CURDIR} && exec ${MAKE} mksystrace
	cd ${.CURDIR}/share/mk \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install
	cd ${.CURDIR}/include \
	    && ${_STCMD_OBJ} ${MAKE} prereq \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} includes
	rm -rf ${BSDOBJDIR}/lib
	cd ${.CURDIR}/lib \
	    && ${MAKE} obj \
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
	grep -v -e '^fd' -e dev/fd ${.CURDIR}/etc/mtree/special | \
	    ${SUDO} mtree -p ${DESTDIR}/ -Uqde
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

release:
	mkdir -p ${DESTDIR} || ${SUDO} mkdir -p ${DESTDIR}
	cd ${.CURDIR} && exec ${MAKE} mksystrace-dest
	cd ${.CURDIR} && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install
	cd ${.CURDIR}/etc && exec ${SUDO} ${_STCMD_DEST} ${MAKE} etc-files
	@sleep 1
	${SUDO} rm -f ${_STFILE_DEST}

do-htman:
	-rm -rf ${BSDOBJDIR}/htman
	mkdir -p ${BSDOBJDIR}/htman/{man,htm}
	cd ${BSDOBJDIR}/htman && env WRITEDIR=${BSDOBJDIR:Q}/htman \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE} ${SHELL}
.for _set _dir in x11 X11R6 base share
	cd ${BSDRELDIR}/${_set}/usr/${_dir}/man && \
	    find * -type f | cpio -pdlu ${BSDOBJDIR}/htman/man
.endfor
	cd ${BSDOBJDIR}/htman && tar xzf \
	    ${BSDRELDIR}/rel/ports${OSrev}.ngz usr/ports/Setup.sh.8 && \
	    ${NROFF} -mdoc usr/ports/Setup.sh.8 \
	    >${BSDOBJDIR}/htman/man/cat8/Setup.sh.0
	cd ${BSDOBJDIR}/htman && tar xzf \
	    ${BSDRELDIR}/rel/pkgutl${OSrev}.ngz usr/mpkg/man/cat?/*.0
	cd ${BSDOBJDIR}/htman/usr/mpkg/man && \
	    find * -type f | cpio -pdlu ${BSDOBJDIR}/htman/man
.for _doc in papers psd smm usd
	mkdir -p ${BSDOBJDIR}/htman/papers/${_doc}
	cd ${BSDOBJDIR}/htman/papers/${_doc} \
	    && lndir ${BSDRELDIR}/base/usr/share/doc/${_doc} \
	    && ${_STCMD} -f ${BSDOBJDIR}/htman/.policy.mk ${MAKE}
.endfor
	cp ${BSDOBJDIR}/share/doc/legal/LICENCE-BSD.0 \
	    ${BSDOBJDIR}/htman/man/cat7/BSD-Licence.0
	BSDOBJDIR=${BSDOBJDIR:Q} BSDSRCDIR=${BSDSRCDIR:Q} \
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
	cd ${.CURDIR}/distrib && ${_STCMD_OBJ} ${MAKE} depend && \
	    exec ${_STCMD_OBJ} ${MAKE}
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
	cd ${.CURDIR} && exec /usr/bin/env -i MAKEFLAGS=${MFLAGS:M*:Q} \
	    HOME=$$(/usr/bin/mktemp -d /var/tmp/buildhome.XXXXXXXXXX) \
	    PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/X11R6/bin TZ=UTC \
	    ${MAKE} BATCH=1 _do-dist 2>&1 | tee -a ${.CURDIR}/Build.log

dist:
	cd ${.CURDIR} && exec /usr/bin/env -i MAKEFLAGS=${MFLAGS:M*:Q} \
	    HOME=$$(/usr/bin/mktemp -d /var/tmp/buildhome.XXXXXXXXXX) \
	    PATH=/bin:/usr/bin:/sbin:/usr/sbin:/usr/X11R6/bin TZ=UTC \
	    ${MAKE} _do-dist 2>&1 | tee -a ${.CURDIR}/Build.log

_DISTS=		base
.ifdef QUICK_DIST2
QUICK_DIST=	implied
NO_LIVECD=	implied
.else
_DISTS+=	x11
.endif
.ifndef QUICK_DIST
_DISTS+=	htman
.endif

.ifdef QUICK_DIST2
.  include "gcc/Makefile.lang"
.endif

_do-dist:
	@h=${HOME:Q}; [[ $$h = $$HOME ]] || exit 1
	@if [[ $$HOME != /var/tmp/buildhome.* ]]; then \
		echo Do not call this target directly; \
		exit 1; \
	fi
	mkdir -p ${HOME}/.etc/systrace
.ifdef QUICK_DIST2
.  if ${NO_JAVA:L} == "no"
	@[[ -e /usr/X11R6/include/X11/X.h && -e /usr/X11R6/lib/libX11.a ]] \
	    || { print 'To build gcc/libjava you must have X11 installed!'; \
		 ${SUDO} rm -rf ${HOME}; \
		 exit 1; }
.  endif
.endif
.ifndef QUICK_DIST
	@c='${CVSROOT}'; [[ $$c = *@(@)*@(:/)* || -e $$c/CVSROOT/config ]] \
	    || { print 'To build a full release CVSROOT must point to the'; \
		 print 'locally mounted MirOS /cvs or a remote repository'; \
		 ${SUDO} rm -rf ${HOME}; \
		 exit 1; }
.endif
	@echo Initialising sudo as ${SUDO:Q}
	${SUDO} true
	@echo ============================================================
	@if [[ ! -e /var/tmp/.buildnotice ]]; then \
		${SUDO} install -c -o 0 -g 0 -m 600 /dev/null \
		    /var/tmp/.buildnotice; \
	fi
	${SUDO} ${MKSH} -c 'echo rm -rf ${HOME} >>/var/tmp/.buildnotice'
	@echo Initiating MirOS Build...
	@date
.ifdef BATCH
	@echo BATCH mode engaged.
.else
	@echo INTERACTIVE mode engaged.
.endif
.ifdef QUICK_DIST
	@echo QUICK dist-build mode active:
	@echo not building ports, package tools, or HTML manual pages.
.  ifdef QUICK_DIST2
	@echo not building XFree86® either.
.  endif
.endif
.ifdef NO_LIVECD
.  ifndef QUICK_DIST
	@echo QUICK dist-build mode active:
.  endif
	@echo not building the baselive CD image.
.endif
	@echo ============================================================
.ifdef NFS_DIST
	@for dir in ${BSDOBJDIR} ${BSDRELDIR}; do \
		if [[ -d $$dir ]]; then \
			${SUDO} rm -rf $$dir/{*,.*}; \
		elif [[ -e $$dir ]]; then \
			print "Warning: '$$dir' not a directory!"; \
			print "The build might fail due to strange"; \
			print "mount combinations, symlinks, etc."; \
			print "and '$$dir' cannot be cleaned either!"; \
		else \
			print "Warning: '$$dir' non-existant; if you"; \
			print "intend an NFS dist you should better"; \
			print "mount something there before starting!"; \
		fi; \
	done
.else
	${SUDO} rm -rf ${BSDOBJDIR} ${BSDRELDIR}
.endif
	cd ${.CURDIR} && exec ${MAKE} distrib-dirs DESTDIR=
	${SUDO} install -d -o 0 -g 0 -m ${DIRMODE} ${BSDRELDIR}/{base,rel,x11}
	cd ${.CURDIR} && exec ${MAKE} b-r
.ifndef QUICK_DIST2
	@date
	cd ${.CURDIR}/X11 && exec ${MAKE} b-r
.endif
	@date
	cd ${.CURDIR}/gcc && exec ${MAKE} b-r
	@date
	cd ${.CURDIR} && exec ${MAKE} release DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR}/gcc && \
	    exec ${SUDO} ${MAKE} install DESTDIR=${BSDRELDIR}/base
.ifndef QUICK_DIST2
	cd ${.CURDIR}/X11 && \
	    exec ${SUDO} ${MAKE} release DESTDIR=${BSDRELDIR}/x11
.endif
	@date
	cd ${.CURDIR} && exec ${MAKE} base-distbuild DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} base-distinstall \
	    DESTDIR=${BSDRELDIR}/base
.ifndef QUICK_DIST
	@date
	t=0; cd ${BSDRELDIR}; \
	if mount 2>&- | fgrep ' on ${BSDRELDIR}/usr ' >&- 2>&-; then \
		${SUDO} umount ${BSDRELDIR}/usr; \
	fi; \
	test ! -e usr || ${SUDO} rm -rf usr; \
	mkdir usr && \
	${SUDO} mount_mfs -s 458752 swap ${BSDRELDIR}/usr && \
	if ! test -e ${BSDRELDIR}/rel/ports${OSrev}.ngz; then \
		cd usr && \
		(umask 002; cvs -Rqz3 -d ${CVSROOT} co -PA ports) && \
		${MKSH} ${.CURDIR}/scripts/mnt-cvsroot ${ANONCVSROOT} . && \
		${SUDO} chown -R root:wsrc ports && \
		cd .. && \
		find usr/ports | sort | cpio -oC512 -Hsv4cpio -Mset | \
		    gzip -n9 | ${SUDO} dd of=rel/ports${OSrev}.ngz && t=1; \
	else \
		${SUDO} tar xzphf ${BSDRELDIR}/rel/ports${OSrev}.ngz \
		    usr/ports/{CVS,M*,S*,essentials/pkgtools,in*} && t=1; \
	fi; \
	test -e ${BSDRELDIR}/rel/pkgutl${OSrev}.ngz || if [[ $$t = 1 ]]; then \
		cd ${BSDRELDIR}/base/dev; ${SUDO} ./MAKEDEV std systrace; \
		cd ..; ${SUDO} rm -rf usr/{mpkg,ports} .etc var/games; \
		${SUDO} mkdir .etc; cd ../usr; ${SUDO} pax -rw -pe -l \
		    ports/{Makefile,Setup.sh,essentials/pkgtools,infra*} \
		    ${BSDRELDIR}/base/usr && cd ${BSDRELDIR}/base && \
		${SUDO} chroot . mksh -c 'cd /usr/ports && make \
		    HOME=/ SUDO= setup' && \
		find usr/mpkg | sort | ${SUDO} cpio -oC512 -Hsv4cpio -Mset | \
		    gzip -n9 | ${SUDO} dd of=../rel/pkgutl${OSrev}.ngz && t=; \
		[[ -z $$t ]] || rm -f ${BSDRELDIR}/rel/pkgutl${OSrev}.ngz; \
		cd ${BSDRELDIR}; ${SUDO} rm -rf base/dev/!(MAKEDEV) \
		    base/usr/{mpkg,ports} base/.etc base/var/games; \
		${SUDO} mkdir -m 0775 ${BSDRELDIR}/base/usr/ports; \
		${SUDO} chown root:wsrc ${BSDRELDIR}/base/usr/ports; \
	fi; \
	cd ${BSDRELDIR}; ${SUDO} umount ${BSDRELDIR}/usr; \
	test -e ${BSDRELDIR}/rel/pkgutl${OSrev}.ngz
	@date
	if [[ ! -e ${BSDRELDIR}/rel/htpsd${OSrev}.ngz || \
	    ! -e ${BSDRELDIR}/rel/htusd${OSrev}.ngz ]]; then \
		cd ${.CURDIR} && exec ${MAKE} do-htman; \
	fi
.endif
	@date
	@echo ============================================================
	@if [[ -e /var/tmp/.buildnotice ]]; then \
		${SUDO} cat /var/tmp/.buildnotice; \
		${SUDO} ${MKSH} /var/tmp/.buildnotice; \
		${SUDO} rm -f /var/tmp/.buildnotice || true; \
		echo ============================================================; \
	fi
	@echo Checking files:
	@echo
.for _set in ${_DISTS}
	-cd ${BSDSRCDIR}/distrib/lists/${_set} && \
	    DESTDIR=${BSDRELDIR:Q}/${_set} RELEASEDIR=${BSDRELDIR:Q}/rel \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/tarsets check
.endfor
	@echo ============================================================
.ifndef BATCH
	@date
	@read a?'Press Return to continue...'
.endif
	@date
	cd ${BSDRELDIR}/base/snapshot && ${SUDO} ${INSTALL} -c \
	    -o root -g wheel -m 444 * ${BSDRELDIR}/rel/
.for _set in ${_DISTS}
	-cd ${BSDSRCDIR}/distrib/lists/${_set} && \
	    DESTDIR=${BSDRELDIR:Q}/${_set} RELEASEDIR=${BSDRELDIR:Q}/rel \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/tarsets make ${OSrev}
.endfor
	-cd ${BSDRELDIR}/rel; \
	    ${SUDO} rm -f CKSUM* RMD160* index.txt; \
	    ( \
		/bin/ls -d1 !(index.txt*); \
		echo CKSUM; \
		echo RMD160.gz; \
		echo RMD160; \
		echo index.txt; \
	    ) | ${SUDO} sort -uo index.txt; \
	    cksum -a cksum -a rmd160 !(@(CKSUM|RMD160)*) | \
	    ${SUDO} tee CKSUM~ | fgrep RMD160 | ${SUDO} sort -uo RMD160; \
	    fgrep -v RMD160 CKSUM~ | ${SUDO} sort -k3 -uo CKSUM; \
	    ${SUDO} rm -f CKSUM~; \
	    ${SUDO} chmod 755 $$(find . -type d); \
	    ${SUDO} chmod 444 $$(find . -type f); \
	    ${SUDO} chown -R 0:0 .
	@echo ============================================================
	@echo Done with MirOS Build.
	@date
	@/bin/ls -Fl ${BSDRELDIR}/rel
	@echo ============================================================
.if !defined(NO_LIVECD)
	cd ${BSDSRCDIR}/distrib/baselive && ${MAKE} it #cleanworkdir
	@echo
	@echo Done with MirOS Snapshot generation.
	@date
	@/bin/ls -Fl ${BSDOBJDIR}/distrib/baselive/livecd${OSrev}.iso
	@echo ============================================================
.endif

.PHONY:	beforeinstall afterinstall mksystrace mksystrace-obj mksystrace-dest \
	build-pre contbuild distrib-dirs b-r release do-htman \
	base-distbuild base-distinstall dist-q dist _do-dist cleandir

.include <bsd.subdir.mk>

cleandir:
	-rm -rf ${BSDOBJDIR}/htman
