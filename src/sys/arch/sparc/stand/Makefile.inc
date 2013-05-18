# $MirOS: src/sys/arch/sparc/stand/Makefile.inc,v 1.7 2007/06/11 21:12:57 tg Exp $
# $OpenBSD: Makefile.inc,v 1.12 2004/07/13 21:03:38 marc Exp $
# $NetBSD: Makefile.inc,v 1.5 1996/02/01 22:33:01 mycroft Exp $

.ifndef MODSRC_SYS_ARCH_SPARC_STAND_MAKEFILE_INC
MODSRC_SYS_ARCH_SPARC_STAND_MAKEFILE_INC=1

BINDIR=		/usr/mdec

.include <bsd.own.mk>
.include "../Makefile.reloc"

KERNBASE?=	$S/../kern
COPTS+=		-Wall -Werror -fno-stack-protector -ffreestanding \
		-fno-zero-initialized-in-bss
.if ${COPTS:M-O*:N-Os}
COPTS+=		-Os
.endif
.if !${COPTS:M-Os}
COPTS+=		-Os
.endif
SACFLAGS=	-D_STANDALONE
CPPFLAGS+=	-I${S} -I${SADIR}/libsa -I. -Dmemmove=memcpy -D_STANDALONE \
		-I${.CURDIR} -Derrno=errno -I${KERNBASE}/include \
		-DSTANDALONE -DRELOC=${RELOC} -DSUN4 -DSUN4C -DSUN_BOOTPARAMS

CLEANFILES+=	machine

.if !make(libdep) && !make(sadep) && !make(salibdir) && !make(kernlibdir) && !make(obj)
.BEGIN:
	@([ X$(S) = X -o -h machine ] || ln -s $(S)/arch/sparc/include machine)
.endif

### Figure out what to use for libkern
LIBKERNDIR=		${.CURDIR}/../libkern

.if exists(${LIBKERNDIR}/obj.${MACHINE})
LIBKERNOBJDIR=		${LIBKERNDIR}/obj.${MACHINE}
.elif exists(${LIBKERNDIR}/obj)
LIBKERNOBJDIR=		${LIBKERNDIR}/obj
.else
LIBKERNOBJDIR=		${LIBKERNDIR}
.endif

DLIBKERN=		${LIBKERNOBJDIR}/libkern.a
LLIBKERN=		-L${LIBKERNOBJDIR} -lkern

### Figure out what to use for libsa
LIBSADIR=		${.CURDIR}/../libsa

.if exists(${LIBSADIR}/obj.${MACHINE})
LIBSAOBJDIR=		${LIBSADIR}/obj.${MACHINE}
.elif exists(${LIBSADIR}/obj)
LIBSAOBJDIR=		${LIBSADIR}/obj
.else
LIBSAOBJDIR=		${LIBSADIR}
.endif

DLIBSA=			${LIBSAOBJDIR}/libsa.a
LLIBSA=			-L${LIBSAOBJDIR} -lsa

### Figure out what to use for libz
LIBZDIR=		${.CURDIR}/../libz

.if exists(${LIBZDIR}/obj.${MACHINE})
LIBZOBJDIR=		${LIBZDIR}/obj.${MACHINE}
.elif exists(${LIBZDIR}/obj)
LIBZOBJDIR=		${LIBZDIR}/obj
.else
LIBZOBJDIR=		${LIBZDIR}
.endif

DLIBZ=			${LIBZOBJDIR}/libz.a
LLIBZ=			-L${LIBZOBJDIR} -lz

.endif
