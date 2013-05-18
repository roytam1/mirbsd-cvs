# $MirOS: src/kern/c/i386/Makefile.inc,v 1.10 2009/01/15 21:50:16 tg Exp $

XSRCS+=		htonl.S htons.S
LSRCS+=		htonl.c htons.c ntohl.c ntohs.c

XSRCS+=		strlen.S
UIF_KUSRCS+=	wcslen.S strlen.S -DWIDEC
LSRCS+=		strlen.c
UIF_LSRCS+=	wcslen.c strlen.c -DWIDEC

UIF_KUSRCS+=	mempcpy.S memcpy.S -DL_mempcpy
UIF_LSRCS+=	mempcpy.c memcpy.c -DL_mempcpy

XSRCS+=		divsi3.S udivsi3.S
KUSRCS+=	fixdfsi.S fixunsdfsi.S

XSRCS+=		ffs.S memchr.S memcmp.S memcpy.S memset.S strcmp.S
LSRCS+=		memchr.c memcmp.c memset.c strcmp.c
LSRCS+=		Lbzero.c Lffs.c
