# $MirOS: src/sys/lib/libkern/Makefile,v 1.16 2011/01/03 19:02:52 tg Exp $
# $NetBSD: Makefile,v 1.31 1996/08/10 04:01:31 mycroft Exp $
# $OpenBSD: Makefile,v 1.18 2004/11/28 07:20:25 mickey Exp $

LIB=		kern
NOPIC=		yes

MACHINE=	${XMACHINE}
MACHINE_ARCH=	${XMACHINE_ARCH}

KERNBASE?=	$S/../kern
.if ${KERNCPPFLAGS:M-DSMALL_KERNEL}
SMALL=		#defined
.endif

CPPFLAGS=	${KERNCPPFLAGS}

.include "${KERNBASE}/c/Makefile.inc"
.include "${KERNBASE}/z/Makefile.adler32"

# Other stuff
SRCS+=	getsn.c bcd.c

# Files to clean up
CLEANFILES+= lib${LIB}.o lib${LIB}.po

install:

.include <bsd.lib.mk>

lib${LIB}.o:: ${OBJS}
	@echo building standard ${LIB} library
	@rm -f lib${LIB}.o
	@${LD} -r -o lib${LIB}.o `${LORDER} ${OBJS} | tsort`
