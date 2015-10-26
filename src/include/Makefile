# $MirOS: src/include/Makefile,v 1.28 2013/09/10 21:24:19 tg Exp $
# $OpenBSD: Makefile,v 1.135 2005/07/10 06:53:44 grange Exp $
# $NetBSD: Makefile,v 1.59 1996/05/15 21:36:43 jtc Exp $
# @(#)Makefile	5.45.1.1 (Berkeley) 5/6/91

# The "rm -rf"s used below are safe because rm doesn't follow symbolic
# links.

.include <bsd.own.mk>

# Missing: mp.h
FILES=	a.out.h adler32.h ar.h assert.h bitstring.h blf.h bm.h bsd_auth.h \
	cast.h cpio.h ctype.h curses.h db.h dbm.h des.h dirent.h disktab.h \
	dlfcn.h elf_abi.h err.h fnmatch.h fstab.h fts.h ftw.h getopt.h glob.h \
	gnu-versions.h grp.h iconv.h ieeefp.h ifaddrs.h inttypes.h iso646.h \
	kvm.h langinfo.h libgen.h limits.h link.h link_aout.h link_elf.h \
	locale.h login_cap.h malloc.h math.h md4.h memory.h \
	mpool.h ndbm.h netdb.h netgroup.h nl_types.h nlist.h ohash.h \
	olf_abi.h paths.h poll.h pwd.h ranlib.h re_comp.h \
	readpassphrase.h regex.h resolv.h rmd160.h search.h setjmp.h \
	sfv.h sgtty.h sha1.h sha2.h signal.h skipjack.h stab.h stdbool.h \
	stdint.h stdio.h stdlib.h string.h strings.h struct.h \
	suma.h sysexits.h tar.h tiger.h time.h ttyent.h tzfile.h unistd.h \
	utf.h utime.h utmp.h vis.h wchar.h wctype.h whirlpool.h

MFILES=	float.h frame.h
LFILES=	errno.h fcntl.h stddef.h syslog.h termios.h stdarg.h varargs.h
KFILES=	md5.h

DIRS=	arpa protocols rpc
LDIRS=	altq crypto ddb dev isofs miscfs net netatalk netinet netinet6 \
	netipx netisdn netnatm nfs ntfs scsi sys ufs uvm

# Directories with an includes target
RDIRS=	../lib/libcompat ../lib/libedit ../lib/libevent ../lib/libexpat \
	../lib/libform ../lib/libkeynote ../lib/libmbfun ../lib/libmenu \
	../lib/libncurses ../lib/libocurses ../lib/libossaudio \
	../lib/libpanel ../lib/libpcap ../lib/libpng ../lib/libpthread \
	../lib/librpcsvc ../lib/libsectok ../lib/libskey ../lib/libssl \
	../lib/libusbhid ../lib/libutil ../lib/libz ../kern/include \
	../usr.bin/lex ../gnu/usr.sbin/sendmail

# Places using Makefile that needs a prerequisite target met before includes
PRDIRS=	../lib/libncurses ../lib/librpcsvc ../lib/libssl/crypto

NOOBJ=	yes

prereq:
	@for i in ${PRDIRS}; do \
		echo preparing in ${.CURDIR}/$$i; \
		cd ${.CURDIR}/$$i && ${MAKE} prereq; \
	done

includes:
	@echo installing ${LDIRS}
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
	cd ${.CURDIR}/../sys/arch/${MACHINE}/include/ && \
	    pax -rw -pa *.h ${DESTDIR}/usr/include/${MACHINE}/
	if [[ ${MACHINE} != ${MACHINE_ARCH} && \
	    -d ../sys/arch/${MACHINE_ARCH}/include ]]; then \
		${INSTALL} -d -o ${BINOWN} -g ${BINGRP} -m ${DIRMODE} \
    	    	    ${DESTDIR}/usr/include/${MACHINE_ARCH}; \
		cd ${.CURDIR}/../sys/arch/${MACHINE_ARCH}/include && \
		    pax -rw -pa *.h ${DESTDIR}/usr/include/${MACHINE_ARCH}/; \
	fi
	ln -sf ${MACHINE} ${DESTDIR}/usr/include/machine
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
	@rm -f ${DESTDIR}/usr/include/ssl && \
	    ln -sf openssl ${DESTDIR}/usr/include/ssl
	@rm -f ${DESTDIR}/usr/include/MirBSD && \
	    ln -sf . ${DESTDIR}/usr/include/MirBSD
	@echo installing ${KFILES}
	@for i in ${KFILES}; do \
		rm -f ${DESTDIR}/usr/include/$$i && \
		ln -s syskern/$$i ${DESTDIR}/usr/include/$$i; \
	done
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

.PHONY: prereq includes
.include <bsd.prog.mk>
