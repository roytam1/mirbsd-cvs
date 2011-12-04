# $MirOS: src/lib/csu/common_elf/Makefile.inc,v 1.4 2005/04/25 23:11:37 tg Exp $
# $NetBSD: Makefile.inc,v 1.23 2003/03/19 16:54:25 ross Exp $

.include <bsd.own.mk>

.if !defined(ELFSIZE) || empty(ELFSIZE)
ELFSIZE=	32
.endif

CFLAGS+=	-fno-omit-frame-pointer -fno-stack-protector -Werror
CPPFLAGS+=	-idirafter ${.CURDIR}/../common_elf
CPPFLAGS+=	-DELFSIZE=${ELFSIZE}
SHARED_FLAGS+=	-DSHARED -DPIC ${PICFLAG}

.PATH:		${.CURDIR}/../common_elf

SRCS+=		crt0.c crti.c
OBJS+=		crt0.o crti.o
# if profiling
#OBJS+=		gcrt0.o
.ifndef __NO_CRTN
SRCS+=		crtn.c
OBJS+=		crtn.o
.endif

# If using an external toolchain, we expect crtbegin/crtend to be
# supplied by that toolchain's run-time support.
GCC3_EXT_TOOLCHAIN?=no
.if ${GCC3_EXT_TOOLCHAIN:L} != "yes"
SRCS+=		crtbegin.c crtend.c
OBJS+=		crtbegin.o crtend.o
.  if !defined(NOPIC) || ${NOPIC:L} == "no"
OBJS+=		crtbeginS.o crtendS.o
.  endif

CPPFLAGS+=	-DDWARF2_EH
#CPPFLAGS+=	-DDSO_HANDLE
#CPPFLAGS+=	-DJCR
.endif

all: ${OBJS}

crt0.o: crt0.c
	${COMPILE.c} -DCRT0 ${.IMPSRC} -o ${.TARGET}.o
	${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

gcrt0.o: crt0.c
	${COMPILE.c} -DMCRT0 ${.ALLSRC} -o ${.TARGET}.o
	${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crti.o: crti.c
	# Don't reorder top-level statements and blocks
	${COMPILE.c} ${.IMPSRC} -o ${.TARGET}.o -fno-unit-at-a-time
	${LD} -X -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtn.o: crtn.c
	${COMPILE.c} ${.IMPSRC} -o ${.TARGET}.o
	${LD} -X -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtbegin.o: crtbegin.c
	${COMPILE.c} ${.IMPSRC} -o ${.TARGET}.o
	${LD} -X -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtbeginS.o: crtbegin.c
	${COMPILE.c} ${SHARED_FLAGS} ${.ALLSRC} -o ${.TARGET}.o
	${LD} -X -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtend.o: crtend.c
	${COMPILE.c} ${.IMPSRC} -o ${.TARGET}.o
	${LD} -X -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtendS.o: crtend.c
	${COMPILE.c} ${SHARED_FLAGS} ${.ALLSRC} -o ${.TARGET}.o
	${LD} -X -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

realinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${NONBINMODE} ${OBJS} ${DESTDIR}/usr/lib/

.include <bsd.prog.mk>
