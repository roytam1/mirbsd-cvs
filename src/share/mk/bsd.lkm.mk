#	$MirOS$
#	$OpenBSD: bsd.lkm.mk,v 1.19 2003/05/20 22:49:13 millert Exp $
# XXX untested

.if exists(${.CURDIR}/../Makefile.inc)
.  include "${.CURDIR}/../Makefile.inc"
.endif

.ifndef	BSD_OWN_MK
.  include <bsd.own.mk>
.endif

.SUFFIXES: .out .o .c .cc .C .y .l .s .8 .7 .6 .5 .4 .3 .2 .1 .0

CFLAGS+=	${COPTS} -D_KERNEL -D_LKM \
		-I${BSDSRCDIR}/sys -I${BSDSRCDIR}/sys/arch
.if ${WARNINGS:L} == "yes"
CFLAGS+=	${CDIAGFLAGS}
.endif

LDFLAGS+=	-r
.if defined(LKM) && !empty(LKM)
SRCS?=		${LKM}.c
.  if !empty(SRCS:N*.h:N*.sh)
OBJS+=		${SRCS:N*.h:N*.sh:R:S/$/.o/g}
LOBJS+=		${LSRCS:.c=.ln} ${SRCS:M*.c:.c=.ln}
.  endif
COMBINED?=	combined.o
.  ifndef POSTINSTALL
POSTINSTALL=	${LKM}install
.  endif

.  if defined(OBJS) && !empty(OBJS)
${COMBINED}: ${OBJS} ${DPADD}
	${LD} ${LDFLAGS} -o ${.TARGET} ${OBJS} ${LDADD}
.  endif

.  ifndef MAN
MAN=		${LKM}.1
.  endif
.endif	# def/not empty LKM

.MAIN: all
all: ${COMBINED} _SUBDIRUSE

.if !target(clean)
clean: _SUBDIRUSE
	rm -f a.out [Ee]rrs mklog core *.core \
	    ${LKM} ${COMBINED} ${OBJS} ${LOBJS} ${CLEANFILES}
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
	    ${COMBINED} ${DESTDIR}${LKMDIR}/${LKM}.o
.      if exists(${.CURDIR}/${POSTINSTALL})
	${INSTALL} ${INSTALL_COPY} -o ${LKMOWN} -g ${LKMGRP} -m 555 \
	    ${.CURDIR}/${POSTINSTALL} ${DESTDIR}${LKMDIR}/
.      endif
.    endif
.  endif

load:	${COMBINED}
	if [ -x ${.CURDIR}/${POSTINSTALL} ]; then \
		modload -d -o $(LKM) -e$(LKM) -p${.CURDIR}/${POSTINSTALL} $(COMBINED); \
	else \
		modload -d -o $(LKM) -e$(LKM) $(COMBINED); \
	fi

unload:
	modunload -n $(LKM)

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
