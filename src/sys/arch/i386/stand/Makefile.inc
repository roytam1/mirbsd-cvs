# $MirOS: src/sys/arch/i386/stand/Makefile.inc,v 1.4 2005/04/29 18:34:57 tg Exp $
# $OpenBSD: Makefile.inc,v 1.36 2004/07/24 17:39:27 millert Exp $

.ifndef MODSRC_SYS_ARCH_I386_STAND_MAKEFILE_INC
MODSRC_SYS_ARCH_I386_STAND_MAKEFILE_INC=1

.include <bsd.own.mk>

REAL_V!=	print '\#include <sys/param.h>\nMirBSD' | ${CC} -E - \
		    | tail -1 | sed s,0x,,
V?=		${REAL_V}
_V=		\"${V}\"
DEBUGLIBS=	No
DEBUGPROGS=	No

CFLAGS+=	-fno-stack-protector -ffreestanding \
		-Os -Wall -Werror -Wno-packed ${DEBUG}
CPPFLAGS+=	-I${S} -I${SADIR}/libsa -I. -Dmemmove=memcpy \
		-I${.CURDIR} -D__BOOT_VER="${_V}" -Derrno=errno
SACFLAGS=	-D_STANDALONE
DEBUGLIBS=	no
DEBUGFLAGS=
# DEBUGFLAGS+=-DDEBUG
# DEBUGFLAGS+=-DGIDT_DEBUG
# DEBUGFLAGS+=-DBIOS_DEBUG
# DEBUGFLAGS+=-DEXEC_DEBUG
# DEBUGFLAGS+=-DALLOC_TRACE
# DEBUGFLAGS+=-g -D_TEST
# DEBUGFLAGS+=-DUNIX_DEBUG
# DEBUGFLAGS+=-DBOOTP_DEBUG -DNETIF_DEBUG -DETHER_DEBUG
# DEBUGFLAGS+=-DNFS_DEBUG -DRPC_DEBUG -DRARP_DEBUG
LINKADDR=	0x40120
LOADADDR=	0x40000
HEAP_LIMIT=	0x90000
BOOTREL=	0x60000
LINKSEG=	${LINKADDR:S/0$//}
LOADSEG=	${LOADADDR:S/0$//}
CPPFLAGS+=	-DSA_LINKSEG=${LINKSEG} -DSA_LOADSEG=${LOADSEG}
CPPFLAGS+=	-DSA_LINKADDR=${LINKADDR} -DSA_LOADADDR=${LOADADDR}

CLEANFILES+=	machine

.if empty(DEBUGFLAGS:M-D_TEST)
SACFLAGS+=	-nostdinc -fno-builtin -fpack-struct
SACFLAGS+=	-Dmemcmp=__builtin_memcmp -Dmemset=__builtin_memset
.endif

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
LIBSA=		${SADIR}/libsa/libsa.a
.else
LIBSA=		${SADIR}/libsa/${__objdir}/libsa.a
.endif
.if exists(${SADIR}/libz/libz.a)
LIBZ=		${SADIR}/libz/libz.a
.else
LIBZ=		${SADIR}/libz/${__objdir}/libz.a
.endif

# NO_NET=no_net
BINDIR=		/usr/mdec

.endif
