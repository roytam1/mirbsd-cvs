# $MirOS: src/sys/arch/i386/stand/pxeboot/Makefile,v 1.10 2009/01/10 11:58:01 tg Exp $
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
INSTALL_STRIP=

LDFLAGS+=	${BOOTLDFLAGS}
CLEANFILES+=	${PROG}.{elf,nm,tmp} ld.out
CLEANFILES+=	crt0.o
SRCS=		srt0.S

SRCS+=	boot.c cmd.c vars.c bootarg.c conf.c devopen.c net.c open.c

LDADD+=		${LLIBSA}
DPADD+=		${DLIBSA}

.PATH:	${S}/stand/boot

${PROG}: $(OBJS) $(DPADD)
	$(LD) $(LDFLAGS) $(OBJS) --start-group $(LDADD) --end-group \
	    -o ${PROG}.elf 2>&1 | tee ld.out
	@if fgrep 'undefined reference' ld.out; then \
		echo "*** Attention: undefined references found!"; \
		rm -f $@; \
		exit 1; \
	fi
	objcopy -x ${PROG}.elf ${PROG}.tmp
	nm ${PROG}.tmp >${PROG}.nm
	@$(SIZE) ${PROG}.elf
	strip --strip-all -R .comment ${PROG}.tmp
	objcopy -O binary ${PROG}.tmp ${PROG}
	@-rm -f ${PROG}.tmp

.else
NOPROG=	yes
.endif

.include <bsd.prog.mk>
