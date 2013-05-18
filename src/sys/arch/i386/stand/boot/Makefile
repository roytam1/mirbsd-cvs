# $MirOS: src/sys/arch/i386/stand/boot/Makefile,v 1.19 2009/01/10 13:41:17 tg Exp $

.include "${.CURDIR}/../Makefile.inc"

S=${.CURDIR}/../../../..
SADIR=${.CURDIR}/..

.include "${KERNBASE}/Makefile.inc"

CPPFLAGS+=	${DEBUGFLAGS}
#CPPFLAGS+=	-DLOUD #-DEXTRALOUD
#CPPFLAGS+=	-DUTEST #-DUHARD #-DUANAL
#CPPFLAGS+=	-DDEBUG_OFS
CPPFLAGS+=	${SACFLAGS:M-[DI]*}
COPTS+=		${SACFLAGS:N-[DI]*}

#AFLAGS+=	-Wa,-R
#AFLAGS+=	-Wa,-a

MAN=		boot.8
MLINKS=		boot.8 boot.cfg.5

.if ${MACHINE_ARCH} == "i386"
PROG=		boot
LD?=		ld
SIZE?=		size
INSTALL_STRIP=
.PATH:		${S}/stand/boot

LDFLAGS+=	${BOOTLDFLAGS}
SRCS=		srt0.S

.ifdef BOOTSELECT_HOOK
SRCS+=		hook.S
CPPFLAGS+=	-DBOOTSELECT_HOOK
.endif

CLEANFILES+=	testmkr ${PROG}.{elf,nm,tmp} ld.out
SRCS+=		boot.c bootarg.c cmd.c conf.c vars.c
LDADD+=		${LLIBSA}
DPADD+=		${DLIBSA}

all:		${PROG}

${PROG}:	$(OBJS) $(DPADD)
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

testmkr: ${PROG}
	cat /usr/mdec/mbrldr ${PROG} | dd conv=osync of=$@
	let size=$$(stat -f %z $@); /usr/mdec/installboot -v -i 1 \
	    $$(( (size - 1) / 512)) /usr/mdec/bootxx $@

.else
NOPROG=		Yes
.endif

.include <bsd.prog.mk>
