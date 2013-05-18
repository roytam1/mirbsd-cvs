# $MirOS: src/sys/arch/i386/stand/boot/Makefile,v 1.25 2009/01/11 14:13:41 tg Exp $

SMALL_BOOT?=	No

.include "${.CURDIR}/../Makefile.inc"

S=${.CURDIR}/../../../..
SADIR=${.CURDIR}/..

.include "${KERNBASE}/Makefile.inc"

CPPFLAGS+=	${DEBUGFLAGS}
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
.PATH:		${S}/stand/boot ${.CURDIR}/../pxeboot

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

.if ${SMALL_BOOT:L} == "no"
# comment this out if trouble
CPPFLAGS+=	-DUSE_PXE -DIN_PXEBOOT
SRCS+=		net.c
.endif

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
	print 2 $$(( size = ($$(stat -f %z ${PROG}) + 511) / 512 + 1 )) | \
	    ${MKSH} $$(realpath ${.OBJDIR})/../bootxx/bxinst | \
	    cat /usr/mdec/mbrldr - ${PROG} | dd conv=osync of=$@
	print -n '\x80\x0\x2\x0\xDB\x4\x2\x0\x1\x0\x0\x0\x81\x0\x0\x0' | \
	    dd conv=notrunc bs=1 seek=462 of=$@
.else
NOPROG=		Yes
.endif

.include <bsd.prog.mk>
