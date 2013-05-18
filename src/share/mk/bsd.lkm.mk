# $MirOS: src/share/mk/bsd.lkm.mk,v 1.5 2005/11/17 18:30:03 tg Exp $
# $OpenBSD: bsd.lkm.mk,v 1.19 2003/05/20 22:49:13 millert Exp $

.if exists(${.CURDIR}/../Makefile.inc)
.  include "${.CURDIR}/../Makefile.inc"
.endif

.ifndef	BSD_OWN_MK
.  include <bsd.own.mk>
.endif

.SUFFIXES: .out .o .c .cc .C .y .l .s .8 .7 .6 .5 .4 .3 .2 .1 .0

.if !${COPTS:M-fhonour-copts} || !${CFLAGS:M-fhonour-copts}
CFLAGS+=	${COPTS}
.endif
.if !${CPPFLAGS:M-D_LKM}
CFLAGS+=	-ffreestanding -fno-builtin-printf -fno-builtin-log
CPPFLAGS+=	-D_KERNEL -D_LKM -I${BSDSRCDIR}/sys -I${BSDSRCDIR}/sys/arch
.endif
.if ${WARNINGS:L} == "yes"
CFLAGS+=	${CDIAGFLAGS}
.endif

LDFLAGS+=	-r
.if defined(LKM) && !empty(LKM)
SRCS?=		${LKM}.c
MAN?=		${LKM}.1
.  if !empty(SRCS:N*.h:N*.sh)
OBJS+=		${SRCS:N*.h:N*.sh:R:S/$/.o/g}
LOBJS+=		${LSRCS:.c=.ln} ${SRCS:M*.c:.c=.ln}
.  endif
POSTINSTALL?=	${LKM}install
POSTUNINSTALL?=	${LKM}uninstall
CLEANFILES+=	${POSTINSTALL} ${POSTUNINSTALL} ${LKM}_init.sh ${LKM}_done.sh

.  if defined(OBJS) && !empty(OBJS)
${LKM}.ko: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o ${.TARGET} ${OBJS} ${LDADD}
.  endif
.endif	# def/not empty LKM

.MAIN: all
all: ${LKM}.ko ${LKM}_init.sh ${LKM}_done.sh _SUBDIRUSE

.if exists(${.CURDIR}/${POSTINSTALL})
all ${LKM}_init.sh: ${POSTINSTALL}

${POSTINSTALL}: ${.CURDIR}/${POSTINSTALL}
	${INSTALL} ${INSTALL_COPY} -m ${BINMODE} $> $@
.endif

.if exists(${.CURDIR}/${POSTUNINSTALL})
all ${LKM}_done.sh: ${POSTUNINSTALL}

${POSTUNINSTALL}: ${.CURDIR}/${POSTUNINSTALL}
	${INSTALL} ${INSTALL_COPY} -m ${BINMODE} $> $@
.endif

${LKM}_init.sh: ${LKM}.ko
	print '#!/bin/sh' >$@
	print 'cd `dirname "$$0"`' >>$@
	print -n 'exec /sbin/modload $$* ' >>$@
	if [[ -x ${POSTINSTALL} ]]; then \
		print -- '-o ${LKM} -p ${POSTINSTALL} ${LKM}.ko'; \
	else \
		print -- '-o ${LKM} ${LKM}.ko'; \
	fi >>$@

${LKM}_done.sh: ${LKM}.ko
	print '#!/bin/sh' >$@
	print 'cd `dirname "$$0"`' >>$@
	print 'rm -f ${LKM}' >>$@
	print -n 'exec /sbin/modunload ' >>$@
	if [[ -x ${POSTUNINSTALL} ]]; then \
		print -- '-p ${POSTUNINSTALL} -n ${LKM}'; \
	else \
		print -- '-n ${LKM}'; \
	fi >>$@

.if !target(clean)
clean: _SUBDIRUSE
	rm -f a.out [Ee]rrs mklog core *.core \
	    ${LKM} ${LKM}.ko ${OBJS} ${LOBJS} ${CLEANFILES}
.endif

cleandir: _SUBDIRUSE clean

.if !target(install)
.  if !target(beforeinstall)
beforeinstall:
.  endif
.  if !target(afterinstall)
afterinstall:
.  endif

.  if !target(realinstall)
realinstall:
.    if defined(LKM) && !empty(LKM)
	${INSTALL} ${INSTALL_COPY} -o ${LKMOWN} -g ${LKMGRP} -m ${LKMMODE} \
	    ${LKM}.ko ${DESTDIR}${LKMDIR}/
.      if exists(${.CURDIR}/${POSTINSTALL})
	${INSTALL} ${INSTALL_COPY} -o ${LKMOWN} -g ${LKMGRP} -m ${BINMODE} \
	    ${.CURDIR}/${POSTINSTALL} ${DESTDIR}${LKMDIR}/
.      endif
.      if exists(${.CURDIR}/${POSTUNINSTALL})
	${INSTALL} ${INSTALL_COPY} -o ${LKMOWN} -g ${LKMGRP} -m ${BINMODE} \
	    ${.CURDIR}/${POSTUNINSTALL} ${DESTDIR}${LKMDIR}/
.      endif
	${INSTALL} ${INSTALL_COPY} -o ${LKMOWN} -g ${LKMGRP} -m ${BINMODE} \
	    ${LKM}_init.sh ${LKM}_done.sh ${DESTDIR}${LKMDIR}/
.    endif
.  endif

load: ${LKM}_init.sh
	@${MKSH} -x $> -d -v

unload: ${LKM}_done.sh
	@${MKSH} -x $>

install: maninstall _SUBDIRUSE
.  if defined(LINKS) && !empty(LINKS)
	@set ${LINKS}; \
	while test $$# -ge 2; do \
		l=${DESTDIR}${LKMDIR}/$$1; \
		shift; \
		t=${DESTDIR}${LKMDIR}/$$1; \
		shift; \
		echo $$t -\> $$l; \
		rm -f $$t; \
		ln $$l $$t || cp $$l $$t; \
	done; true
.  endif

maninstall: afterinstall
afterinstall: realinstall
realinstall: beforeinstall
.endif

.if !target(lint)
lint: ${LOBJS}
.  if defined(LOBJS) && !empty(LOBJS)
	@${LINT} ${LINTFLAGS} ${LDFLAGS:M-L*} ${LOBJS} ${LDADD}
.  endif
.endif

.if ${NOMAN:L} == "no"
.  include <bsd.man.mk>
.endif

.include <bsd.obj.mk>
.include <bsd.dep.mk>
.include <bsd.subdir.mk>
.include <bsd.sys.mk>

.PHONY: load unload
