# $MirOS: src/kern/c/i386/Makefile.inc,v 1.6 2008/08/01 18:09:19 tg Exp $

SRCS+=		htonl.S htons.S
LSRCS+=		htonl.c htons.c ntohl.c ntohs.c

SRCS+=		strlen.S
UIF_KUSRCS+=	wcslen.S strlen.S -DWIDEC
LSRCS+=		strlen.c
UIF_LSRCS+=	wcslen.c strlen.c -DWIDEC

SRCS+=		divsi3.S udivsi3.S

SRCS+=		bzero.S ffs.S memchr.S memcmp.S memcpy.S memset.S strcmp.S
LSRCS+=		memchr.c memcmp.c memset.c strcmp.c
LSRCS+=		Lbzero.c Lffs.c
