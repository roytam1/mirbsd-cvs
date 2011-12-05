# $MirOS: src/lib/csu/common_elf/Makefile.inc,v 1.8 2005/10/21 11:02:39 tg Exp $
# $NetBSD: Makefile.inc,v 1.23 2003/03/19 16:54:25 ross Exp $

.include <bsd.own.mk>

.if !defined(ELFSIZE) || empty(ELFSIZE)
ELFSIZE=	32
.endif

COPTS+=		-fno-omit-frame-pointer -fno-stack-protector -Werror
CPPFLAGS+=	-idirafter ${.CURDIR}/../common_elf
CPPFLAGS+=	-DELFSIZE=${ELFSIZE}
SHARED_FLAGS+=	-DSHARED -DPIC ${PICFLAG}

.PATH:		${.CURDIR}/../common_elf

SRCS+=		crt0.c crti.c crtn.c
OBJS+=		crt0.o crti.o crtn.o
# if profiling
#OBJS+=		gcrt0.o

# These are now provided by GCC 3
#SRCS+=		crtbegin.c crtend.c
#OBJS+=		crtbegin.o crtend.o
#.  if !defined(NOPIC) || ${NOPIC:L} == "no"
#OBJS+=		crtbeginS.o crtendS.o
#.  endif
#CPPFLAGS+=	-DDWARF2_EH # -DDSO_HANDLE -DJCR

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
	${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtn.o: crtn.c
	${COMPILE.c} ${.IMPSRC} -o ${.TARGET}.o
	${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtbegin.o: crtbegin.c
	${COMPILE.c} ${.IMPSRC} -o ${.TARGET}.o
	${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtbeginS.o: crtbegin.c
	${COMPILE.c} ${SHARED_FLAGS} ${.ALLSRC} -o ${.TARGET}.o
	${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtend.o: crtend.c
	${COMPILE.c} ${.IMPSRC} -o ${.TARGET}.o
	${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

crtendS.o: crtend.c
	${COMPILE.c} ${SHARED_FLAGS} ${.ALLSRC} -o ${.TARGET}.o
	${LD} -x -r -o ${.TARGET} ${.TARGET}.o
	@rm -f ${.TARGET}.o

realinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} \
	    -m ${NONBINMODE} ${OBJS} ${DESTDIR}/usr/lib/

.include <bsd.prog.mk>
