# $MirOS: src/sys/arch/i386/stand/boot/Makefile,v 1.9 2006/07/23 23:41:28 tg Exp $

.include "${.CURDIR}/../Makefile.inc"

S=${.CURDIR}/../../../..
SADIR=${.CURDIR}/..
RL_VAL=0x17

CPPFLAGS+=	${DEBUGFLAGS} -DRL_VAL=${RL_VAL}
#CPPFLAGS+=	-DWANT_ELTORITO_CHECK
#CPPFLAGS+=	-DLOUD #-DEXTRALOUD
#CPPFLAGS+=	-DUTEST #-DUHARD #-DUANAL
#CPPFLAGS+=	-DDEBUG_OFS
CPPFLAGS+=	$(SACFLAGS)

#AFLAGS+=	-Wa,-R
#AFLAGS+=	-Wa,-a

MAN=	boot.8
MLINKS=	boot.8 boot.cfg.8

.if ${MACHINE_ARCH} == "i386"
PROG=		boot
LD?=		ld
SIZE?=		size
LDFLAGS+=	-nostdlib -Bstatic --no-undefined
INSTALL_STRIP=
.PATH:		${S}/stand/boot

.if defined(DEBUGFLAGS) && !empty(DEBUGFLAGS:M-D_TEST)
CLEANFILES+=	srt0.o
SRCS=		crt0.c
.else
LDFLAGS+=	-Ttext $(LINKADDR) -N -x -noinhibit-exec
CLEANFILES+=	crt0.o
SRCS=		srt0.S
.endif

.ifdef BOOTSELECT_HOOK
SRCS+=		hook.S
CPPFLAGS+=	-DBOOTSELECT_HOOK
.endif

CLEANFILES+=	${.CURDIR}/disasm testmkr ${PROG}.nm ld.out
SRCS+=		boot.c bootarg.c cmd.c conf.c vars.c
LDADD=		${LIBSA} ${LIBZ}
DPADD=		${LIBSA} ${LIBZ}

all:		${PROG}

${PROG}:	$(OBJS) $(DPADD)
	$(LD) $(LDFLAGS) $(OBJS) --start-group $(LDADD) --end-group \
	    -o ${PROG} 2>&1 | tee ld.out
	@if fgrep 'undefined reference' ld.out; then \
		echo "*** Attention: undefined references found!"; \
		exit 1; \
	  else exit 0; fi
	nm ${PROG} >${PROG}.nm
	@if [ x"$$(fgrep 'T _rval' ${PROG}.nm)" != \
	    x"00040170 T _rval" ]; then \
		echo "ERROR: Value of RL_VAL (${RL_VAL}) must be adjusted!"; \
		echo "  Example: 00040170 T _rval => 0x17 (take the two"; \
		echo "   digits before the last 0 in hexadecimal); place"; \
		echo "   that in Makefile and adjust the \$${PROG} rule!"; \
		echo "  The problematic sym: $$(fgrep 'T _rval' ${PROG}.nm)"; \
		exit 1; \
	fi
	@$(SIZE) ${PROG}
	strip --strip-all -R .comment ${PROG}
	objcopy -O binary ${PROG}

disasm:	${.CURDIR}/disasm

${.CURDIR}/disasm:	${PROG}
	ndisasm -b16 -o${LINKADDR} ${PROG} >${.CURDIR}/disasm

testmkr: ${PROG}
	cat /usr/mdec/mbrldr ${PROG} | dd conv=osync of=$@
	let size=$$(stat -f %z $@); /usr/mdec/installboot -v -i 1 \
	    $$(( (size - 1) / 512)) /usr/mdec/bootxx $@

.else
NOPROG=		Yes
.endif

.include <bsd.prog.mk>
