# $MirOS: src/sys/arch/i386/stand/boot/Makefile,v 1.34 2010/01/10 19:21:35 tg Exp $

SMALL_BOOT?=	No
BOOTLDR_PATH?=	${.CURDIR}

.include "${.CURDIR}/../Makefile.inc"

S=${.CURDIR}/../../../..
SADIR=${.CURDIR}/..

.include "${KERNBASE}/Makefile.inc"

CPPFLAGS+=	${DEBUGFLAGS}
CPPFLAGS+=	${SACFLAGS:M-[DI]*}
COPTS+=		${SACFLAGS:N-[DI]*}

.if defined(MBSD_PREFIX) && !empty(MBSD_PREFIX)
CPPFLAGS+=	-DMBSD_PREFIX=\"${MBSD_PREFIX:Q}\"
.endif

#AFLAGS+=	-Wa,-R
#AFLAGS+=	-Wa,-a

MAN=		boot.8
MLINKS+=	boot.8 boot.cfg.5
MLINKS+=	boot.8 pxeboot.8

.if ${MACHINE_ARCH} == "i386"
PROG=		boot
LD?=		ld
SIZE?=		size
INSTALL_STRIP=
.PATH:		${S}/stand/boot ${.CURDIR}/../pxeboot

LDFLAGS+=	${BOOTLDFLAGS}
SRCS=		srt0.S

.if defined(BOOTSELECT_HOOK) && (${BOOTSELECT_HOOK:L} != "no")
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
# comment this out if trouble
CPPFLAGS+=	-DUSE_DOSFS -DUSE_DOSFS_LETTERS
# comment this out if trouble
#CPPFLAGS+=	-DUSE_USTARFS
.else
CPPFLAGS+=	-DSMALL_BOOT
V=		${REAL_V}-small
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
	@$(SIZE) ${PROG}.elf
	objcopy -x -R .comment ${PROG}.elf ${PROG}.tmp
	nm ${PROG}.tmp >${PROG}.nm
	${MKSH} ${BOOTLDR_PATH}/idt_fixup.sh ${PROG}.tmp ${PROG}
	@-rm -f ${PROG}.tmp

TESTMBR?=	mbrldr
testmkr: ${PROG}
	print 2 $$(( size = ($$(stat -f %z ${PROG}) + 511) / 512 + 1 )) | \
	    ${MKSH} $$(realpath ${.OBJDIR})/../bootxx/bxinst | \
	    cat /usr/mdec/${TESTMBR} - ${PROG} | dd conv=osync of=$@
	print -n '\x80\x0\x2\x0\xDB\x4\x2\x0\x1\x0\x0\x0\x81\x0\x0\x0' | \
	    dd conv=notrunc bs=1 seek=462 of=$@
.else
NOPROG=		Yes
.endif

BOOTXX_TAR?=	/usr/mdec/bootxx.tar
KERNEL_TAR?=	bsd.rd
CLEANFILES+=	boot.cfg ${KERNEL_TAR}
testtar: .PHONY ${PROG}
	echo 'echo Hello, Testtar!' >boot.cfg
	tar -b 1 -M uidgid -cf - ${PROG} boot.cfg ${KERNEL_TAR} | \
	    cat ${BOOTXX_TAR} - >$@
	tar -tvvf $@

.include <bsd.prog.mk>
BINMODE=	${SHAREMODE}
