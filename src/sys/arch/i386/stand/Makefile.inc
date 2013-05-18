# $MirOS: src/sys/arch/i386/stand/Makefile.inc,v 1.20 2008/08/03 21:02:03 tg Exp $
# $OpenBSD: Makefile.inc,v 1.40 2007/11/26 10:26:02 deraadt Exp $

.ifndef MODSRC_SYS_ARCH_I386_STAND_MAKEFILE_INC
MODSRC_SYS_ARCH_I386_STAND_MAKEFILE_INC=1

.include <bsd.own.mk>

REAL_V!=	print '\#include <sys/param.h>\nMirBSD' | ${CC} -E - \
		    | tail -1 | sed s,0x,,
V?=		${REAL_V}
_V=		"${V}"

KERNBASE?=	$S/../kern
HOSTCFLAGS:=	${CFLAGS} ${COPTS}
COPTS+=		-fno-stack-protector -ffreestanding -Wall -Wno-packed \
		-fno-align-loops -fno-align-jumps -fno-omit-frame-pointer \
		-Werror ${DEBUG}
.if ${COPTS:M-O*:N-Os}
COPTS+=		-Os
.endif
.if !${COPTS:M-Os}
COPTS+=		-Os
.endif
HOSTCPPFLAGS:=	${CPPFLAGS}
CPPFLAGS+=	-I${S} -I${SADIR}/libsa -I. \
		-I${.CURDIR} -D__BOOT_VER=${_V:Q}
SACFLAGS=	-D_STANDALONE
DEBUGFLAGS=
# DEBUGFLAGS+=-DDEBUG
# DEBUGFLAGS+=-DGIDT_DEBUG
# DEBUGFLAGS+=-DBIOS_DEBUG
# DEBUGFLAGS+=-DEXEC_DEBUG
# DEBUGFLAGS+=-DALLOC_TRACE
# DEBUGFLAGS+=-DUNIX_DEBUG
# DEBUGFLAGS+=-DBOOTP_DEBUG -DNETIF_DEBUG -DETHER_DEBUG
# DEBUGFLAGS+=-DNFS_DEBUG -DRPC_DEBUG -DRARP_DEBUG
M_LINKADDR=	0x40120
M_LOADADDR=	0x40000
CPPFLAGS+=	-DSA_LINKADDR=${M_LINKADDR} -DSA_LINKSEG=${M_LINKADDR:S/0$//}
CPPFLAGS+=	-DSA_LOADADDR=${M_LOADADDR} -DSA_LOADSEG=${M_LOADADDR:S/0$//}
HEAP_LIMIT=	0x90000
BOOTREL=	0x60000

CLEANFILES+=	machine

SACFLAGS+=	-nostdinc -fno-builtin -fpack-struct

.if !make(libdep) && !make(sadep) && !make(salibdir) && !make(kernlibdir) && !make(obj)
.BEGIN:
	@([ X$(S) = X -o -h machine ] || ln -s $(S)/arch/i386/include machine)
.endif


.if exists(${SADIR}/etc/assym.h)
CPPFLAGS+=	-I${SADIR}/etc
.else
CPPFLAGS+=	-I${SADIR}/etc/${__objdir}
.endif
.if exists(${SADIR}/libsa/libsa.a)
DLIBSA=		${SADIR}/libsa/libsa.a
LLIBSA=		-L${SADIR}/libsa -lsa
.else
DLIBSA=		${SADIR}/libsa/${__objdir}/libsa.a
LLIBSA=		-L${SADIR}/libsa/${__objdir} -lsa
.endif

# NO_NET=no_net
BINDIR=		/usr/mdec

prereq: .NOTMAIN
# empty

.PHONY: prereq

.endif
