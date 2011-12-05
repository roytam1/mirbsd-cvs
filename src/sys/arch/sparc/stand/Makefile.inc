# $MirOS: src/sys/arch/sparc/stand/Makefile.inc,v 1.3 2006/06/16 21:52:52 tg Exp $
# $OpenBSD: Makefile.inc,v 1.12 2004/07/13 21:03:38 marc Exp $
# $NetBSD: Makefile.inc,v 1.5 1996/02/01 22:33:01 mycroft Exp $

BINDIR=		/usr/mdec

.include "../Makefile.reloc"

CFLAGS+=	-fno-stack-protector -ffreestanding -Os -Wall -Werror
SACFLAGS=	-D_STANDALONE
CPPFLAGS+=	-I${S} -I${SADIR}/libsa -I. -Dmemmove=memcpy -D_STANDALONE \
		-I${.CURDIR} -Derrno=errno \
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

LIBKERN=		${LIBKERNOBJDIR}/libkern.a

### Figure out what to use for libsa
LIBSADIR=		${.CURDIR}/../libsa

.if exists(${LIBSADIR}/obj.${MACHINE})
LIBSAOBJDIR=		${LIBSADIR}/obj.${MACHINE}
.elif exists(${LIBSADIR}/obj)
LIBSAOBJDIR=		${LIBSADIR}/obj
.else
LIBSAOBJDIR=		${LIBSADIR}
.endif

LIBSA=			${LIBSAOBJDIR}/libsa.a

### Figure out what to use for libz
LIBZDIR=		${.CURDIR}/../libz

.if exists(${LIBZDIR}/obj.${MACHINE})
LIBZOBJDIR=		${LIBZDIR}/obj.${MACHINE}
.elif exists(${LIBZDIR}/obj)
LIBZOBJDIR=		${LIBZDIR}/obj
.else
LIBZOBJDIR=		${LIBZDIR}
.endif

LIBZ=			${LIBZOBJDIR}/libz.a
