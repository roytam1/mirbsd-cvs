# $MirOS: src/sys/arch/sparc/stand/Makefile.inc,v 1.11 2008/08/03 21:02:04 tg Exp $
# $OpenBSD: Makefile.inc,v 1.12 2004/07/13 21:03:38 marc Exp $
# $NetBSD: Makefile.inc,v 1.5 1996/02/01 22:33:01 mycroft Exp $

.ifndef MODSRC_SYS_ARCH_SPARC_STAND_MAKEFILE_INC
MODSRC_SYS_ARCH_SPARC_STAND_MAKEFILE_INC=1

BINDIR=		/usr/mdec

.include <bsd.own.mk>
.include "../Makefile.reloc"

REAL_V!=	print '\#include <sys/param.h>\nMirBSD' | ${CC} -E - \
		    | tail -1 | sed s,0x,,
V?=		${REAL_V}
_V=		"${V}"

KERNBASE?=	$S/../kern
HOSTCFLAGS:=	${CFLAGS} ${COPTS}
COPTS+=		-Wall -Werror -fno-stack-protector -ffreestanding \
		-fno-zero-initialized-in-bss
.if ${COPTS:M-O*:N-Os}
COPTS+=		-Os
.endif
.if !${COPTS:M-Os}
COPTS+=		-Os
.endif
SACFLAGS=	-D_STANDALONE
HOSTCPPFLAGS:=	${CPPFLAGS}
CPPFLAGS+=	-I${S} -I${SADIR}/libsa -D_STANDALONE -D__BOOT_VER=${_V:Q} \
		-I. -I${.CURDIR} -Derrno=errno -I${KERNBASE}/include \
		-DSTANDALONE -DRELOC=${RELOC} -DSUN4 -DSUN4C -DSUN_BOOTPARAMS

CLEANFILES+=	machine

.if !make(libdep) && !make(sadep) && !make(salibdir) && !make(kernlibdir) && !make(obj)
.BEGIN:
	@([ X$(S) = X -o -h machine ] || ln -s $(S)/arch/sparc/include machine)
.endif

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

.endif
