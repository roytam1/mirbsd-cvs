# $MirOS: src/lib/libc/Makefile,v 1.5 2005/07/01 13:51:24 tg Exp $
# $OpenBSD: Makefile,v 1.23 2005/06/29 14:05:08 mickey Exp $
#
# All library objects contain sccsid strings by default; they may be
# excluded as a space-saving measure.  To produce a library that does
# not contain these strings, delete -DLIBC_SCCS and -DSYSLIBC_SCCS
# from CFLAGS below.  To remove these strings from just the system call
# stubs, remove just -DSYSLIBC_SCCS from CFLAGS in Makefile.inc.

.include <bsd.own.mk>

SHLIB_VERSION?=		38.0	# note: If changes were made to the file
#				# src/lib/libc/include/thread_private.h or
#				# system calls have been added/changed,
#				# libpthread must also be updated.
LIB=c
LINTFLAGS+=-z
CLEANFILES+=tags

LIBCSRCDIR=${.CURDIR}
.include "${LIBCSRCDIR}/Makefile.inc"

copy-to-libkern:	copy-to-libkern-machind copy-to-libkern-machdep

.if make(copy-to-libkern)
copy-to-libkern-machind: ${KSRCS}
	cp -p ${.ALLSRC} ${LIBKERN}
.if defined(KINCLUDES) && !empty(KINCLUDES)
	(cd ${.CURDIR} ; cp -p ${KINCLUDES} ${LIBKERN})
.endif

copy-to-libkern-machdep: ${KMSRCS}
.if defined(KMSRCS) && !empty(KMSRCS)
	cp -p ${.ALLSRC} ${LIBKERN}/arch/${MACHINE_ARCH}
.endif
.if defined(KMINCLUDES) && !empty(KMINCLUDES)
	(cd ${.CURDIR} ; cp -p ${KMINCLUDES} ${LIBKERN}/arch/${MACHINE_ARCH})
.endif

rm-from-libkern:
	for i in ${KSRCS}; do rm -f ${LIBKERN}/$$i; done
.if defined(KMSRCS) && !empty(KMSRCS)
	for i in ${KMSRCS}; do rm -f ${LIBKERN}/arch/${MACHINE_ARCH}/$$i; done
.endif
.endif

all: tags
tags: ${SRCS}
	ctags -w ${.ALLSRC:M*.c}
	egrep "^SYSENTRY(.*)|^ENTRY(.*)|^FUNC(.*)|^SYSCALL(.*)" \
	    /dev/null ${.ALLSRC:M*.S} | \
	    sed "s;\([^:]*\):\([^(]*\)(\([^, )]*\)\(.*\);\3 \1 /^\2(\3\4$$/;" \
	    >> tags; sort -o tags tags

beforeinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 tags \
		${DESTDIR}/var/db/lib${LIB}.tags

.include <bsd.lib.mk>
