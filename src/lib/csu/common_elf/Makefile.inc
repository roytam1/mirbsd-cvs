# $MirOS: src/lib/csu/common_elf/Makefile.inc,v 1.14 2008/12/26 16:27:41 tg Exp $
# $NetBSD: Makefile.inc,v 1.23 2003/03/19 16:54:25 ross Exp $

.include "${.CURDIR}/../Makefile.inc"

.if !defined(ELFSIZE) || empty(ELFSIZE)
ELFSIZE=	32
.endif

.if ${DEBUGLIBS:L} == "yes"
_DISCARD=	-X
_SODISCARD=	-X
.else
_DISCARD=	-x
_SODISCARD=	-g -x
.endif

COPTS+=		-fno-stack-protector-all -fno-stack-protector \
		-fno-omit-frame-pointer -fno-unit-at-a-time -Werror
CPPFLAGS+=	-idirafter ${.CURDIR}/../common_elf
CPPFLAGS+=	-DELFSIZE=${ELFSIZE}

.PATH:		${.CURDIR}/../common_elf

SRCS+=		crt0.c crti.c crtn.c
# if profiling
#SRCS+=		gcrt0.c

.ifndef HAVE_VERSION_SPECIFIC_GCC_LIBS
# These are now provided by GCC 3
.else
CPPFLAGS+=	-DHAVE_VERSION_SPECIFIC_GCC_LIBS
SRCS+=		crtbegin.c crtbeginT.c crtend.c
.  if !defined(NOPIC) || ${NOPIC:L} == "no"
SRCS+=		crtbeginS.c crtendS.c
.  endif
CPPFLAGS+=	-DDWARF2_EH -DDSO_HANDLE # -DJCR
.endif

COPYFILES+=	crt0.c gcrt0.c
COPYFILES+=	crtbegin.c crtbeginT.c
COPYFILES+=	crtbegin.c crtbeginS.c
COPYFILES+=	crtend.c crtendS.c
.for _s _d in ${COPYFILES}
CLEANFILES+=	${_d}
beforedepend: ${_d}
${_d}: ${_s}
	cp -f ${.ALLSRC} $@
.endfor

CLEANFILES+=	sun_crt1.o sun_crtn.o sun_crti.o
sunstuff: sun_crt1.o sun_crtn.o sun_crti.o

sun_crt1.o: ${DESTDIR}/usr/lib/crt0.o ${DESTDIR}/usr/lib/crtbegin.o
	${LD} -r -o $@ ${.ALLSRC}

sun_crtn.o: ${DESTDIR}/usr/lib/crtend.o ${DESTDIR}/usr/lib/crtn.o
	${LD} -r -o $@ ${.ALLSRC}

sun_crti.o: ${DESTDIR}/usr/lib/crti.o
	${LD} -r -o $@ ${.ALLSRC}

crt0.o: crt0.c
	${COMPILE.c} -DCRT0 -fPIE -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

gcrt0.o: crt0.c
	${COMPILE.c} -DMCRT0 -fPIE -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

crti.o: crti.c
	${COMPILE.c} -g0 -fPIE -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

crtn.o: crtn.c
	${COMPILE.c} -fPIE -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

crtbegin.o: crtbegin.c
	${COMPILE.c} -fPIE -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

crtbeginS.o: crtbegin.c
	${COMPILE.c} -DSHARED -DPIC ${PICFLAG} -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

crtbeginT.o: crtbegin.c
	${COMPILE.c} -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

crtend.o: crtend.c
	${COMPILE.c} -fPIE -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

crtendS.o: crtend.c
	${COMPILE.c} -DSHARED -DPIC ${PICFLAG} -o $@.o ${.IMPSRC}
	${LD} ${_DISCARD} -r -o $@ $@.o
	@rm -f $@.o

realinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${NONBINMODE} ${OBJS} ${DESTDIR}/usr/lib/

.PHONY: sunstuff

OBJS+=		${SRCS:N*.h:N*.sh:R:S/$/.o/g}
all: ${OBJS}

.include <bsd.prog.mk>
