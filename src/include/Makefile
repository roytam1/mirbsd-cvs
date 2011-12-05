# $MirOS: src/include/Makefile,v 1.9 2005/12/04 17:50:19 tg Exp $
# $OpenBSD: Makefile,v 1.135 2005/07/10 06:53:44 grange Exp $
# $NetBSD: Makefile,v 1.59 1996/05/15 21:36:43 jtc Exp $
# @(#)Makefile	5.45.1.1 (Berkeley) 5/6/91

# The "rm -rf"s used below are safe because rm doesn't follow symbolic
# links.

.include <bsd.own.mk>

# Missing: mp.h
FILES=	a.out.h ar.h assert.h bitstring.h blf.h bm.h bsd_auth.h cast.h \
	cpio.h ctype.h curses.h db.h dbm.h des.h dirent.h disktab.h \
	dlfcn.h elf_abi.h err.h fnmatch.h fstab.h fts.h ftw.h getopt.h \
	glob.h grp.h ieeefp.h ifaddrs.h inttypes.h iso646.h kvm.h \
	langinfo.h libgen.h limits.h link.h link_aout.h link_elf.h \
	locale.h login_cap.h malloc.h math.h md4.h md5.h memory.h \
	mpool.h ndbm.h netdb.h netgroup.h nl_types.h nlist.h ohash.h \
	olf_abi.h paths.h poll.h pwd.h ranlib.h re_comp.h \
	readpassphrase.h regex.h resolv.h rmd160.h search.h setjmp.h \
	sgtty.h sha1.h sha2.h signal.h skipjack.h stab.h stdbool.h \
	stddef.h stdint.h stdio.h stdlib.h string.h strings.h struct.h \
	sysexits.h tar.h time.h ttyent.h tzfile.h unistd.h utime.h \
	utmp.h vis.h wchar.h #wctype.h

MFILES=	float.h frame.h
LFILES=	errno.h fcntl.h syslog.h termios.h stdarg.h varargs.h

DIRS=	arpa protocols rpc
LDIRS=	altq crypto ddb dev isofs miscfs net netatalk netinet netinet6 \
	netipx netisdn netnatm nfs ntfs scsi sys ufs uvm

# Directories with an includes target
RDIRS=	../lib/libcdk ../lib/libcompat ../lib/libcurses ../lib/libedit \
	../lib/libevent ../lib/libexpat ../lib/libform ../lib/libkeynote \
	../lib/libmenu ../lib/libocurses ../lib/libossaudio ../lib/libpanel \
	../lib/libpcap ../lib/libpng ../lib/libpthread ../lib/librpcsvc \
	../lib/libsectok ../lib/libskey ../lib/libssl ../lib/libusbhid \
	../lib/libutil ../lib/libz \
	../usr.bin/lex ../gnu/usr.sbin/sendmail \
	../sys/arch/${MACHINE}

# Places using Makefile that needs a prerequisite target met before includes
PRDIRS=	../lib/libcdk ../lib/librpcsvc ../lib/libssl/crypto \
	../sys/arch/${MACHINE}/stand

NOOBJ=	yes

# Change SYS_INCLUDE in bsd.own.mk to "symlinks" if you don't want copies

prereq:
	@for i in ${PRDIRS}; do \
		echo preparing in ${.CURDIR}/$$i; \
		cd ${.CURDIR}/$$i && ${MAKE} prereq; \
	done

includes:
	@echo installing ${FILES}
	@for i in ${FILES}; do \
		cmp -s $$i ${DESTDIR}/usr/include/$$i || \
		    ${INSTALL} ${INSTALL_COPY} -m ${NONBINMODE} \
		    $$i ${DESTDIR}/usr/include/$$i; \
	done
	@echo installing ${DIRS}
	@for i in ${DIRS}; do \
		${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
		    ${DESTDIR}/usr/include/$$i; \
		cd ${.CURDIR}/$$i && for j in *.[ih]; do \
			cmp -s $$j ${DESTDIR}/usr/include/$$i/$$j || \
			    ${INSTALL} ${INSTALL_COPY} -m ${NONBINMODE} \
			    $$j ${DESTDIR}/usr/include/$$i/$$j; \
		done; \
	done
	@ln -sf openssl ${DESTDIR}/usr/include/ssl
	@echo installing ${LFILES}
	@for i in ${LFILES}; do \
		rm -f ${DESTDIR}/usr/include/$$i && \
		ln -s sys/$$i ${DESTDIR}/usr/include/$$i; \
	done
	@echo installing ${MFILES}
	@for i in ${MFILES}; do \
		rm -f ${DESTDIR}/usr/include/$$i && \
		ln -s machine/$$i ${DESTDIR}/usr/include/$$i; \
	done
	@for i in ${RDIRS}; do \
		echo installing in ${.CURDIR}/$$i; \
		cd ${.CURDIR}/$$i && ${MAKE} includes; \
	done
	chown -R ${BINOWN}:${BINGRP} ${DESTDIR}/usr/include
	find ${DESTDIR}/usr/include -type f | xargs chmod a=r
	find ${DESTDIR}/usr/include -type d | xargs chmod u=rwx,go=rx

copies:
	@echo copies: ${LDIRS}
	@for i in ${LDIRS}; do \
		rm -rf ${DESTDIR}/usr/include/$$i && \
		${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
		    ${DESTDIR}/usr/include/$$i ; \
	done
	cd ../sys; \
	pax -rw -pa -L \
	    $$(find ${LDIRS} -follow -type f -name '*.h' \
	    '!' -path 'dev/microcode/*' -print) ${DESTDIR}/usr/include
	cd ${DESTDIR}/usr/include && rm -rf ${MACHINE} ${MACHINE_ARCH} machine
	${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
	    ${DESTDIR}/usr/include/${MACHINE}
	pax -rw -pa -s "|\.\./sys/arch/${MACHINE}/include||" \
	    ../sys/arch/${MACHINE}/include/*.h \
	    ${DESTDIR}/usr/include/${MACHINE}
	if test ${MACHINE} != ${MACHINE_ARCH} -a \
	    -d ../sys/arch/${MACHINE_ARCH}/include; then \
		${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
    	    	    ${DESTDIR}/usr/include/${MACHINE_ARCH}; \
		pax -rw -pa -s "|\.\./sys/arch/${MACHINE_ARCH}/include||" \
		    ../sys/arch/${MACHINE_ARCH}/include/*.h \
		    ${DESTDIR}/usr/include/${MACHINE_ARCH}; \
	fi
	ln -sf ${MACHINE} ${DESTDIR}/usr/include/machine

symlinks:
	@echo symlinks: ${LDIRS}
	@for i in ${LDIRS}; do \
		rm -rf ${DESTDIR}/usr/include/$$i && \
		ln -s /sys/$$i ${DESTDIR}/usr/include/$$i; \
	done
	cd ${DESTDIR}/usr/include && rm -rf ${MACHINE} ${MACHINE_ARCH} machine
	ln -s /sys/arch/${MACHINE}/include ${DESTDIR}/usr/include/${MACHINE}
	if test ${MACHINE} != ${MACHINE_ARCH} -a \
	    -d ../sys/arch/${MACHINE_ARCH}/include ; then \
		ln -s /sys/arch/${MACHINE_ARCH}/include \
		    ${DESTDIR}/usr/include/${MACHINE_ARCH} ; \
	fi
	ln -sf ${MACHINE} ${DESTDIR}/usr/include/machine

includes: ${SYS_INCLUDE}

.PHONY: prereq includes copies symlink
.include <bsd.prog.mk>
