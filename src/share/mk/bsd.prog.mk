# $MirOS: src/share/mk/bsd.prog.mk,v 1.23 2006/06/17 20:08:08 tg Exp $
# $OpenBSD: bsd.prog.mk,v 1.44 2005/04/15 17:18:57 espie Exp $
# $NetBSD: bsd.prog.mk,v 1.55 1996/04/08 21:19:26 jtc Exp $
# @(#)bsd.prog.mk	5.26 (Berkeley) 6/25/91

.if !defined(BSD_PROG_MK)
BSD_PROG_MK=1

.if exists(${.CURDIR}/../Makefile.inc)
.  include "${.CURDIR}/../Makefile.inc"
.endif

.if !defined(BSD_OWN_MK)
.  include <bsd.own.mk>
.endif

.SUFFIXES:	.out .o .s .S .c .m .cc .cxx .y .l .9 .8 .7 .6 .5 .4 .3 .2 .1 .0

.if ${WARNINGS:L} == "yes"
CFLAGS+=	${CDIAGFLAGS}
CXXFLAGS+=	${CXXDIAGFLAGS}
.endif
.if !${COPTS:M-fhonour-copts} || !${CFLAGS:M-fhonour-copts}
CFLAGS+=	${COPTS}
.endif
CXXFLAGS+=	${CXXOPTS}
HOSTCFLAGS?=	${CFLAGS}

.if defined(PROG) && !empty(PROG)
SRCS?=	${PROG}.c
.  if !empty(SRCS:N*.h:N*.sh)
OBJS+=	${SRCS:N*.h:N*.sh:R:S/$/.o/g}
LOBJS+=	${LSRCS:.c=.ln} ${SRCS:M*.c:.c=.ln}
.  endif

.  if !empty(SRCS:M*.C) || !empty(SRCS:M*.cc) || !empty(SRCS:M*.cxx)
LINKER?=	${CXX}
.  else
LINKER?=	${CC}
.  endif

.  if defined(OBJS) && !empty(OBJS)
.    if ${RTLD_TYPE} == "dyld"
LINK.prog?=	${LINKER} ${LDFLAGS} ${LDSTATIC} ${OBJS} ${LDADD}
.    else
LINK.prog?=	${LINKER} ${LDFLAGS} ${LDSTATIC} \
		${OBJS} -Wl,--start-group ${LDADD} -Wl,--end-group
.    endif

${PROG}: ${CRTI} ${CRTBEGIN} ${LIBCRT0} ${OBJS} ${LIBC} ${DPADD} ${CRTEND} ${CRTN}
	${LINK.prog} -o $@
.  else
LINK.prog?=	NO
.  endif

MAN?=	${PROG}.1
.endif	# def/not empty PROG

.MAIN: all
all: ${PROG} _SUBDIRUSE

.if !target(clean)
clean: _SUBDIRUSE
	rm -f a.out [Ee]rrs mklog core *.core \
	    ${PROG} ${OBJS} ${LOBJS} ${CLEANFILES}
.endif

cleandir: _SUBDIRUSE clean
.if ${NOMAN:L} != "no"
	rm -f *.cat?
.endif

.if !target(install)
.  if !target(beforeinstall)
beforeinstall:
.  endif
.  if !target(afterinstall)
afterinstall:
.  endif

.  if !target(realinstall)
realinstall:
.    if defined(PROG) && !empty(PROG)
.      if (${OBJECT_FMT} == "Mach-O") && (${LINK.prog} != "NO")
	@echo Relinking ${PROG}
	${LINK.prog} -o ${PROG}
.      endif
	${INSTALL} ${INSTALL_COPY} ${INSTALL_STRIP} -o ${BINOWN} -g ${BINGRP} \
	    -m ${BINMODE} ${PROG} ${DESTDIR}${BINDIR}/
.    endif
.  endif

install: maninstall _SUBDIRUSE
.  if defined(LINKS) && !empty(LINKS)
.    for lnk file in ${LINKS}
	@l=${DESTDIR}${lnk}; \
	 t=${DESTDIR}${file}; \
	 echo $$t -\> $$l; \
	 rm -f $$t; ln $$l $$t || cp $$l $$t
.    endfor
.  endif

maninstall: afterinstall
afterinstall: realinstall
realinstall: beforeinstall
.endif	# !target install

.if !target(lint)
.  if empty(LINTFLAGS:M-l*)
LINTFLAGS+=	-lstdc
.  endif
lint: ${LOBJS}
.  if defined(LOBJS) && !empty(LOBJS)
	@${LINT} ${LINTFLAGS} ${LDFLAGS:M-L*} ${LOBJS} ${LDADD:N-W*}
.  endif
.endif

.if ${NOMAN:L} == "no"
.  include <bsd.man.mk>
.endif

.include <bsd.obj.mk>
.include <bsd.dep.mk>
.include <bsd.subdir.mk>
.include <bsd.sys.mk>

.endif
