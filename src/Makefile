# $MirOS: src/Makefile,v 1.148 2012/07/14 12:13:33 tg Exp $
# $OpenBSD: Makefile,v 1.103 2004/05/03 15:18:18 drahn Exp $

.if defined(MAKECONF) && exists(${MAKECONF})
.  error MAKECONF is set to '${MAKECONF}', you don't want this!
.endif
.include <bsd.own.mk>
.include "Makefile.inc"
.if exists(gcc/Makefile.lang)
.  include "gcc/Makefile.lang"
.else
NO_ADA?=	Yes
NO_PASCAL?=	Yes
.endif
NOMAN?=		no
CVSROOT?=	/cvs
ANONCVSROOT?=	_anoncvs@anoncvs.mirbsd.org:/cvs
_SAFEPATH=	/bin:/usr/bin:/sbin:/usr/sbin:/usr/X11R6/bin
BATCH?=		No
TSCOMPRESS?=	Yes

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
	cd ${.CURDIR}/lib && ${MAKE} obj && exec ${_STCMD_OBJ} ${MAKE} depend
	cd ${.CURDIR}/lib/csu \
	    && ${_STCMD_OBJ} ${MAKE} \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install NOMAN=yes

build-lib:
	cd ${.CURDIR}/lib/libc \
	    && ${_STCMD_OBJ} ${MAKE} \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install NOMAN=yes
	${SUDO} /sbin/ldconfig -R
	cd ${.CURDIR}/lib \
	    && ${_STCMD_OBJ} ${MAKE} \
	    && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install NOMAN=yes
	${SUDO} /sbin/ldconfig -R
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
	cd ${DESTDIR}/var/anoncvs && \
	    if [[ ! -h var || $$(readlink var) != . ]]; then \
		${SUDO} rm -f var; \
		${SUDO} ln -s . var; \
	fi
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
	cd ${.CURDIR} && exec ${MAKE} build-lib DESTDIR=
	cd ${.CURDIR} && exec ${MAKE} contbuild DESTDIR=

release:
	mkdir -p ${DESTDIR} || ${SUDO} mkdir -p ${DESTDIR}
	cd ${.CURDIR} && exec ${MAKE} mksystrace-dest
	cd ${.CURDIR} && exec ${SUDO} ${_STCMD_DEST} ${MAKE} install
	cd ${.CURDIR}/etc && exec ${SUDO} ${_STCMD_DEST} ${MAKE} etc-files
	@sleep 1
	${SUDO} rm -f ${_STFILE_DEST}

do-htman:
	-${SUDO} rm -rf ${BSDOBJDIR}/htman ${BSDRELDIR}/htman
	${SUDO} mkdir -p ${BSDOBJDIR}/htman ${BSDRELDIR}/htman
	${SUDO} chown $$(id -u) ${BSDOBJDIR}/htman ${BSDRELDIR}/htman
	BSDOBJDIR=${BSDOBJDIR:Q} BSDSRCDIR=${BSDSRCDIR:Q} \
	    BSDRELDIR=${BSDRELDIR:Q} OSrev=${OSrev:Q} \
	    ${SHELL} ${.CURDIR}/scripts/genhtman.sh
	${SUDO} chown -R 0:0 ${BSDRELDIR}/htman/*
	${SUDO} chmod -R a=rX ${BSDRELDIR}/htman/*

do-htinfopapers:
	cd ${BSDOBJDIR} && env WRITEDIR=${BSDOBJDIR:Q} \
	    ${SHELL} ${BSDSRCDIR}/scripts/systrace.mk ${MAKE} ${SHELL}
.for _doc in papers psd smm usd
	cd ${BSDOBJDIR}/htman/papers/${_doc} && ${_STCMD_OBJ} ${MAKE}
.endfor
	cd ${.CURDIR} && ${_STCMD_OBJ} ${MAKE} _do-htinfo
	-rm -f ${BSDOBJDIR}/.policy.mk

_do-htinfo:
	cd ${BSDOBJDIR}/gnu/usr.bin/binutils/bfd/doc && \
	    rm -f {bfd,bfdint}.html && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gnu/usr.bin/binutils/bfd/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/bfd/doc/bfd.texinfo && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gnu/usr.bin/binutils/bfd/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/bfd/doc/bfdint.texi && \
	    cp {bfd,bfdint}.html ${BSDOBJDIR}/htman/texinfo/
	cd ${BSDOBJDIR}/gnu/usr.bin/binutils/binutils/doc && \
	    rm -f binutils.html && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gnu/usr.bin/binutils/binutils/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/binutils/doc/binutils.texi && \
	    cp binutils.html ${BSDOBJDIR}/htman/texinfo/
	cd ${BSDOBJDIR}/gnu/usr.bin/binutils/gas/doc && \
	    rm -f as.html && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gnu/usr.bin/binutils/gas/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/gas/doc/as.texinfo && \
	    cp as.html ${BSDOBJDIR}/htman/texinfo/
	cd ${BSDOBJDIR}/gnu/usr.bin/binutils/gdb/doc && \
	    rm -f {gdb,gdbint,stabs,annotate}.html && \
	    makeinfo --no-split --html \
	    -I ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/mi \
	    -I ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/doc/gdb.texinfo && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/doc/gdbint.texinfo && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/doc/stabs.texinfo && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/gdb/doc/annotate.texinfo && \
	    cp {gdb,gdbint,stabs,annotate}.html ${BSDOBJDIR}/htman/texinfo/
	cd ${BSDOBJDIR}/gnu/usr.bin/binutils/ld && \
	    rm -f ld{,int}.html && \
	    makeinfo --no-split --html \
	    -I ${BSDSRCDIR}/gnu/usr.bin/binutils/ld \
	    -I ${BSDSRCDIR}/gnu/usr.bin/binutils/bfd/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/ld/ld.texinfo && \
	    makeinfo --no-split --html \
	    -I ${BSDSRCDIR}/gnu/usr.bin/binutils/ld \
	    -I ${BSDSRCDIR}/gnu/usr.bin/binutils/bfd/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/binutils/ld/ldint.texinfo && \
	    cp ld{,int}.html ${BSDOBJDIR}/htman/texinfo/
	cd ${BSDOBJDIR}/gnu/usr.bin/cvs/doc && \
	    rm -f cvs{,client}.html && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gnu/usr.bin/cvs/doc \
	    ${BSDSRCDIR}/gnu/usr.bin/cvs/doc/cvs.texinfo && \
	    makeinfo --no-split --html \
	    ${BSDSRCDIR}/gnu/usr.bin/cvs/doc/cvsclient.texi && \
	    cp cvs{,client}.html ${BSDOBJDIR}/htman/texinfo/
	cd ${BSDOBJDIR}/gcc/gcc && \
	    rm -f {cpp{,internals},gcc{,int}}.html && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gcc/gcc/doc/include \
	    ${BSDSRCDIR}/gcc/gcc/doc/cpp.texi && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gcc/gcc/doc/include \
	    ${BSDSRCDIR}/gcc/gcc/doc/gcc.texi && \
	    makeinfo --no-split --html -I ${BSDSRCDIR}/gcc/gcc/doc/include \
	    ${BSDSRCDIR}/gcc/gcc/doc/gccint.texi && \
	    makeinfo --no-split --html \
	    ${BSDSRCDIR}/gcc/gcc/doc/cppinternals.texi && \
	    cp {cpp{,internals},gcc{,int}}.html ${BSDOBJDIR}/htman/texinfo/
.if ${NO_ADA:L} == "no"
	cd ${BSDOBJDIR}/gcc/gcc && \
	    rm -f gnat{_ugn_unw,_rm,-style}.html && \
	    makeinfo --no-split --html \
	    -I ${BSDSRCDIR}/gcc/gcc/doc/include -I ${BSDSRCDIR}/gcc/gcc/ada \
	    doc/gnat_ugn_unw.texi && \
	    makeinfo --no-split --html \
	    -I ${BSDSRCDIR}/gcc/gcc/doc/include -I ${BSDSRCDIR}/gcc/gcc/ada \
	    ${BSDSRCDIR}/gcc/gcc/ada/gnat_rm.texi && \
	    makeinfo --no-split --html \
	    -I ${BSDSRCDIR}/gcc/gcc/doc/include -I ${BSDSRCDIR}/gcc/gcc/ada \
	    ${BSDSRCDIR}/gcc/gcc/ada/gnat-style.texi && \
	    cp gnat{_ugn_unw,_rm,-style}.html ${BSDOBJDIR}/htman/texinfo/
.endif
.if ${NO_PASCAL:L} == "no"
	cd ${BSDOBJDIR}/gcc/gpcdoc && \
	    cp gpc{,-hr,s{,-de,-hr}}.html ${BSDOBJDIR}/htman/texinfo/
.endif

base-distbuild:
	cd ${.CURDIR} && exec ${MAKE} mksystrace-obj
	cd ${.CURDIR}/distrib && ${_STCMD_OBJ} ${MAKE} depend && \
	    exec ${_STCMD_OBJ} ${MAKE}
	-rm -f ${_STFILE_OBJ}

base-distinstall:
	cd ${.CURDIR} && exec ${MAKE} mksystrace-dest
.if (${MACHINE_ARCH} == "i386")
	${INSTALL} -c -o ${BINOWN} -g ${BINGRP} -m ${BINMODE} \
	    ${.CURDIR}/distrib/common/ekeyrng ${DESTDIR}/usr/libexec/
.endif
	-rm -rf ${_STFILE_OBJ} ${DESTDIR}/snapshot
	${INSTALL} -d -o root -g wheel -m 755 ${DESTDIR}/snapshot
	cd ${DESTDIR} && for file in usr/mdec/*{boot,mbr}*; do \
		[[ -e $$file ]] || continue; \
		${INSTALL} -c -o root -g wheel -m 444 $$file snapshot/; \
	done
	cd ${.CURDIR}/distrib && exec ${_STCMD_DEST} ${MAKE} install
	cd ${.CURDIR}/share/man && exec ${_STCMD_DEST} ${MAKE} makedb
	cd ${.CURDIR}/gnu/usr.bin/texinfo && exec ${_STCMD_DEST} \
	    ${MAKE} -f Makefile.bsd-wrapper mkinfodir
	-rm -f ${_STFILE_DEST}

dist:
	cd ${.CURDIR} && exec /usr/bin/env -i MAKEFLAGS=${MFLAGS:M*:Q} \
	    HOME=$$(/usr/bin/mktemp -d /var/tmp/buildhome.XXXXXXXXXX) \
	    PATH=${_SAFEPATH} TZ=UTC \
	    ${MAKE} _do-dist 2>&1 | tee -a ${.CURDIR}/Build.log
	@date | tee -a ${.CURDIR}/Build.log
	-[[ -d ${BSDRELDIR}/rel && -s ${.CURDIR}/Build.log ]] && \
	    ${SUDO} cp ${.CURDIR}/Build.log ${BSDRELDIR}/rel/

dist-q:
	cd ${.CURDIR} && exec /usr/bin/env -i MAKEFLAGS=${MFLAGS:M*:Q} \
	    HOME=$$(/usr/bin/mktemp -d /var/tmp/buildhome.XXXXXXXXXX) \
	    PATH=${_SAFEPATH} TZ=UTC BATCH=Yes \
	    ${MAKE} _do-dist 2>&1 | tee -a ${.CURDIR}/Build.log
	@date | tee -a ${.CURDIR}/Build.log
	-[[ -d ${BSDRELDIR}/rel && -s ${.CURDIR}/Build.log ]] && \
	    ${SUDO} cp ${.CURDIR}/Build.log ${BSDRELDIR}/rel/

_DISTS=		base
.ifdef QUICK_DIST2
QUICK_DIST=	implied
.else
_DISTS+=	x11
.endif
.ifndef QUICK_DIST
_DISTS+=	htman
.endif
DIST_RESTART?=	0

_do-dist:
	@h=${HOME:Q}; [[ $$h = $$HOME ]] || exit 1
	@if [[ $$HOME != /var/tmp/buildhome.* ]]; then \
		echo Do not call this target directly; \
		exit 1; \
	fi
	@echo Initialising sudo as ${SUDO:Q}
	${SUDO} true
	mkdir -p ${HOME}/.etc/systrace
.ifdef QUICK_DIST2
.  if ${NO_JAVA:L} == "no"
	@[[ -e /usr/X11R6/include/X11/X.h && -e /usr/X11R6/lib/libX11.a ]] || \
	    {	print 'To build gcc/libjava you must have X11 installed!'; \
		${SUDO} rm -rf ${HOME}; \
		exit 1; \
	}
.  endif
.endif
.ifndef QUICK_DIST
	@c='${CVSROOT}'; [[ $$c = @(:@(ext|pserver):|*@(@))*@(:/)* || \
	    -e $$c/CVSROOT/config ]] || { \
		print 'To build a full release CVSROOT must point to the'; \
		print 'locally mounted MirOS /cvs or a remote repository'; \
		${SUDO} rm -rf ${HOME}; \
		exit 1; \
	}
.endif
	@if ! ${SUDO} mksh -c '[[ -w /var/anoncvs/bin/cvs ]]'; then \
		print 'Your /var/anoncvs must be mounted read-write'; \
		${SUDO} rm -rf ${HOME}; \
		exit 1; \
	fi
	@echo ============================================================
	@if [[ ! -e /var/tmp/.buildnotice ]]; then \
		${SUDO} install -c -o 0 -g 0 -m 600 /dev/null \
		    /var/tmp/.buildnotice; \
	fi
	${SUDO} ${MKSH} -c 'echo rm -rf ${HOME} >>/var/tmp/.buildnotice'
	@${SUDO} rm -f ${BSDRELDIR}/rel/Build.log
	@echo Initiating MirOS Build...
	@date
.if ${BATCH:L} == "yes"
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
	@echo ============================================================
.if ${DIST_RESTART} > 0
	@print not removing ${BSDOBJDIR:Q} and ${BSDRELDIR:Q}
.elif defined(NFS_DIST)
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
.if ${DIST_RESTART} == 0
	cd ${.CURDIR} && exec ${MAKE} b-r
.elif ${DIST_RESTART} == 1
	cd ${.CURDIR} && ${MAKE} build-lib && exec ${MAKE} contbuild
.elif ${DIST_RESTART} == 2
	cd ${.CURDIR} && exec ${MAKE} contbuild
.endif
	${SUDO} /sbin/ldconfig -R
.ifndef QUICK_DIST2
	@date
.  if ${DIST_RESTART} < 4
	cd ${.CURDIR}/X11 && exec ${MAKE} b-r
.  endif
.endif
	${SUDO} /sbin/ldconfig -R
	@date
.if ${DIST_RESTART} < 5
	cd ${.CURDIR}/gcc && exec ${MAKE} b-r
.endif
	${SUDO} /sbin/ldconfig -R
	@date
.if ${DIST_RESTART} < 6
	cd ${.CURDIR} && exec ${MAKE} release DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR}/gcc && \
	    exec ${SUDO} ${MAKE} install DESTDIR=${BSDRELDIR}/base
.  ifndef QUICK_DIST2
	cd ${.CURDIR}/X11 && \
	    exec ${SUDO} ${MAKE} release DESTDIR=${BSDRELDIR}/x11
.  endif
.endif
	@date
.if ${DIST_RESTART} < 7
	cd ${.CURDIR} && exec ${MAKE} base-distbuild DESTDIR=${BSDRELDIR}/base
	cd ${.CURDIR} && exec ${SUDO} ${MAKE} base-distinstall \
	    DESTDIR=${BSDRELDIR}/base
.endif
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
		mkdir -m 0775 ports/{Distfiles,Packages} && \
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
	if [[ ! -e ${BSDRELDIR}/rel/htmi${OSrev}.ngz || \
	    ! -e ${BSDRELDIR}/rel/htmd${OSrev}.ngz ]]; then \
		cd ${.CURDIR} && exec ${MAKE} do-htman; \
	fi
.endif
	col -bx <${BSDRELDIR}/base/usr/share/man/cat7/install.${MACHINE}.0 \
	    >${BSDOBJDIR}/INSTALL
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
.if ${BATCH:L} != "yes"
	@date
	@read a?'Press Return to continue...'
.endif
	@date
	${SUDO} ${INSTALL} -c -o root -g wheel -m 444 \
	    ${BSDOBJDIR}/INSTALL ${BSDRELDIR}/base/snapshot/* ${BSDRELDIR}/rel/
	${SUDO} ${INSTALL} -c -o root -g wheel -m 444 \
	    ${BSDSRCDIR}/distrib/empty.ngz ${BSDRELDIR}/rel/fixes${OSrev}.ngz
	${SUDO} ${INSTALL} -c -o root -g wheel -m 444 \
	    ${BSDSRCDIR}/distrib/empty.ngz ${BSDRELDIR}/rel/site${OSrev}.ngz
.for _set in ${_DISTS}
	-cd ${BSDSRCDIR}/distrib/lists/${_set} && env doz=${TSCOMPRESS:L:Q} \
	    DESTDIR=${BSDRELDIR:Q}/${_set} RELEASEDIR=${BSDRELDIR:Q}/rel \
	    ${SUDO} ${SHELL} ${BSDSRCDIR}/scripts/tarsets make ${OSrev}
.endfor
	-cd ${BSDRELDIR}/rel; \
	    ${SUDO} rm -f CKSUM* index.txt; \
	    ( \
		/bin/ls -d1 !(@(Build|index.txt)*); \
		echo CKSUM; \
		echo CKSUM.gz; \
		echo index.txt; \
	    ) | ${SUDO} sort -uo index.txt; \
	    sort -k3 |& exec 3>&p; exec 4<&p; \
	    sort |& exec 5>&p; exec 6<&p; \
	    cksum -a cksum -a rmd160 -a tiger !(@(Build|CKSUM)*) | \
	    while IFS= read -r line; do \
		if [[ $$line = *" = "+([0-9a-fA-F]) ]]; then \
			print -ru5 "$$line"; \
		else \
			print -ru3 "$$line"; \
		fi; \
	    done; \
	    exec 3>&-; exec 5>&-; \
	    (cat <&4; cat <&6) | ${SUDO} dd of=CKSUM 2>/dev/null; \
	    ${SUDO} chmod 755 $$(find . -type d); \
	    ${SUDO} chmod 444 $$(find . -type f); \
	    ${SUDO} chown -R 0:0 .
	@echo ============================================================
	@echo Done with MirOS Build.
.if ${DIST_RESTART} != 0
	@${SUDO} touch ${BSDRELDIR}/rel/Not_an_official_release!
.endif
	@/bin/ls -Fl ${BSDRELDIR}/rel
	@date
	@echo ============================================================

cflags:
	@print -r -- CFLAGS=\'${CFLAGS:N-Werror:Q} ${COPTS:N-Werror:Q}\'

.PHONY:	afterinstall b-r base-distbuild base-distinstall beforeinstall \
	build-pre cflags cleandir contbuild dist dist-q distrib-dirs \
	do-htman mksystrace mksystrace-dest mksystrace-obj release _do-dist

.include <bsd.subdir.mk>

cleandir:
	-rm -rf ${BSDOBJDIR}/htman
