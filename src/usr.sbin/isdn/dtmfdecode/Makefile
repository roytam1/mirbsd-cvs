# $MirOS$
# $NetBSD: Makefile,v 1.3 2004/03/19 08:07:22 jmc Exp $

PROG            =       dtmfdecode
SRC             =       dtmfdecode.c

# libm is only necessary if USE_COS is defined in the source
#LDADD		+=	-lm
#DPADD		+=	${LIBM}
#CPPFLAGS	+=	-DUSE_COS

UUDECODE_FILES	=	dtmfsounds.al
CLEANFILES	+=	${UUDECODE_FILES}

test:	${PROG} ${UUDECODE_FILES}
	./${PROG} < dtmfsounds.al

.SUFFIXES: .uue

.uue:
	uudecode -o $@ $<

.include <bsd.prog.mk>
