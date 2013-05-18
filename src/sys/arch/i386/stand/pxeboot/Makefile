# $MirOS: src/sys/arch/i386/stand/pxeboot/Makefile,v 1.5 2006/06/30 23:18:05 tg Exp $
# $OpenBSD: Makefile,v 1.1 2004/03/19 13:48:19 tom Exp $

.include "${.CURDIR}/../Makefile.inc"

S=${.CURDIR}/../../../..
SADIR=${.CURDIR}/..

CPPFLAGS+=	${DEBUGFLAGS} -DLINKADDR=${LINKADDR} \
		-D__INTERNAL_LIBSA_CREAD -DIN_PXEBOOT
CPPFLAGS+=	${SACFLAGS:M-[DI]*}
COPTS+=		${SACFLAGS:N-[DI]*}

#AFLAGS+=	-Wa,-R
#AFLAGS+=	-Wa,-a

MAN=		pxeboot.8

.if ${MACHINE_ARCH} == "i386"
PROG=		pxeboot
LD?=		ld
SIZE?=		size
LDFLAGS+=	-nostdlib -Bstatic
INSTALL_STRIP=

LDFLAGS+=	-Ttext $(LINKADDR) -N -x -noinhibit-exec
CLEANFILES+=	${.CURDIR}/disasm ld.out
CLEANFILES+=	crt0.o
SRCS=		srt0.S

SRCS+=	boot.c cmd.c vars.c bootarg.c conf.c devopen.c net.c open.c

LDADD=	${LIBSA} ${LIBZ}
DPADD=	${LIBSA} ${LIBZ}

.PATH:	${S}/stand/boot

${PROG}: $(OBJS) $(DPADD)
	$(LD) $(LDFLAGS) -o ${PROG} $(OBJS) $(LDADD) 2>&1 | tee ld.out
	@if fgrep 'undefined reference' ld.out; then \
		echo "*** Attention: undefined references found!"; \
		exit 1; \
	  else exit 0; fi
	@$(SIZE) ${PROG}
	strip --strip-all -R .comment ${PROG}
	objcopy -O binary ${PROG}

disasm:	${.CURDIR}/disasm

${.CURDIR}/disasm:	${PROG}
	ndisasm -b16 -o${LINKADDR} ${PROG} >${.CURDIR}/disasm

.else
NOPROG=	yes
.endif

.include <bsd.prog.mk>
