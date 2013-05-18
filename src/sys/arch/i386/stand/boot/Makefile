# $MirOS: src/sys/arch/i386/stand/boot/Makefile,v 1.17 2009/01/03 13:42:11 tg Exp $

.include "${.CURDIR}/../Makefile.inc"

S=${.CURDIR}/../../../..
SADIR=${.CURDIR}/..
RL_VAL=0x17

.include "${KERNBASE}/Makefile.inc"

CPPFLAGS+=	${DEBUGFLAGS} -DRL_VAL=${RL_VAL}
#CPPFLAGS+=	-DWANT_ELTORITO_CHECK
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
LDFLAGS+=	-nostdlib -Bstatic --no-undefined
INSTALL_STRIP=
.PATH:		${S}/stand/boot

LDFLAGS+=	-Ttext $(M_LINKADDR) -N -noinhibit-exec
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
	@if [ x"$$(fgrep 'T _rval' ${PROG}.nm)" != \
	    x"00040170 T _rval" ]; then \
		echo "ERROR: Value of RL_VAL (${RL_VAL}) must be adjusted!"; \
		echo "  Example: 00040170 T _rval => 0x17 (take the two"; \
		echo "   digits before the last 0 in hexadecimal); place"; \
		echo "   that in Makefile and adjust the \$${PROG} rule!"; \
		echo "  The problematic sym: $$(fgrep 'T _rval' ${PROG}.nm)"; \
		exit 1; \
	fi
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
