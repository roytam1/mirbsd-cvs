# $MirOS$

LIB=		mdsup
NOMAN=		Yes

.include <bsd.own.mk>

KERNNOGCC=	#defined
KERNBASE?=	${.CURDIR}/../../kern
KERNPICKSRCS=	Yes
.include "${KERNBASE}/c/Makefile.inc"

SRCS=

.if ${MACHINE_ARCH} == "i386"
SRCS+=		divsi3.S udivsi3.S
SRCS+=		bzero.S memcpy.S

.elif ${MACHINE_ARCH} == "sparc"
CPPFLAGS+=	-DSTRONG_SPARC
COPTS+=		-msoft-float

SRCS+=		bzero.S memcpy.c
SRCS+=		mul.S umul.S
SRCS+=		rem.S sdiv.S udiv.S urem.S

.else
.  error unknown machine architecture ${MACHINE_ARCH}
.endif

SRCS+=		adddi3.c anddi3.c ashldi3.c ashrdi3.c cmpdi2.c divdi3.c \
		iordi3.c lshldi3.c lshrdi3.c moddi3.c muldi3.c negdi2.c \
		notdi2.c qdivrem.c subdi3.c ucmpdi2.c udivdi3.c umoddi3.c \
		xordi3.c

.include <bsd.lib.mk>
