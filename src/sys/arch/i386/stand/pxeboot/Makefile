# $MirOS: src/sys/arch/i386/stand/pxeboot/Makefile,v 1.9 2008/08/01 15:43:46 tg Exp $
# $OpenBSD: Makefile,v 1.3 2007/11/25 18:25:32 deraadt Exp $

.include "${.CURDIR}/../Makefile.inc"

S=${.CURDIR}/../../../..
SADIR=${.CURDIR}/..

.include "${KERNBASE}/Makefile.inc"

CPPFLAGS+=	${DEBUGFLAGS} \
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

LDFLAGS+=	-Ttext $(M_LINKADDR) -N -x -noinhibit-exec
CLEANFILES+=	ld.out
CLEANFILES+=	crt0.o
SRCS=		srt0.S

SRCS+=	boot.c cmd.c vars.c bootarg.c conf.c devopen.c net.c open.c

LDADD+=		${LLIBSA}
DPADD+=		${DLIBSA}

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

.else
NOPROG=	yes
.endif

.include <bsd.prog.mk>
