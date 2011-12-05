# $MirOS: src/sys/lib/libkern/Makefile,v 1.2 2005/03/06 21:28:05 tg Exp $
# $NetBSD: Makefile,v 1.31 1996/08/10 04:01:31 mycroft Exp $
# $OpenBSD: Makefile,v 1.18 2004/11/28 07:20:25 mickey Exp $

LIB=	kern
NOPIC=	yes

MACHINE=	${XMACHINE}
MACHINE_ARCH=	${XMACHINE_ARCH}

M=	${.CURDIR}/arch/${MACHINE_ARCH}

CPPFLAGS=	-I$M ${KERNCPPFLAGS}

.if exists ($M/Makefile.inc)
.PATH:	$M
.include "$M/Makefile.inc"
.endif

.if (${MACHINE_ARCH} != "alpha" && ${MACHINE} != "sgi" && \
    ${MACHINE_ARCH} != "sparc64") && ${MACHINE} != "amd64" && \
    ${MACHINE} != "hppa64"
# Quad support
SRCS+=	adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c iordi3.c \
	lshldi3.c lshrdi3.c moddi3.c muldi3.c negdi2.c notdi2.c qdivrem.c \
	subdi3.c  ucmpdi2.c udivdi3.c umoddi3.c xordi3.c
.endif

# Other stuff
SRCS+=	getsn.c srandom.c bcd.c strchr.c taitime.c

# Files to clean up
CLEANFILES+= lib${LIB}.o lib${LIB}.po

install:

.include <bsd.lib.mk>

lib${LIB}.o:: ${OBJS}
	@echo building standard ${LIB} library
	@rm -f lib${LIB}.o
	@${LD} -r -o lib${LIB}.o `${LORDER} ${OBJS} | tsort`
