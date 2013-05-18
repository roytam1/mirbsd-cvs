# $MirOS: src/kern/c/i386/Makefile.inc,v 1.7 2008/08/03 21:02:01 tg Exp $

XSRCS+=		htonl.S htons.S
LSRCS+=		htonl.c htons.c ntohl.c ntohs.c

XSRCS+=		strlen.S
UIF_KUSRCS+=	wcslen.S strlen.S -DWIDEC
LSRCS+=		strlen.c
UIF_LSRCS+=	wcslen.c strlen.c -DWIDEC

XSRCS+=		divsi3.S udivsi3.S

XSRCS+=		bzero.S ffs.S memchr.S memcmp.S memcpy.S memset.S strcmp.S
LSRCS+=		memchr.c memcmp.c memset.c strcmp.c
LSRCS+=		Lbzero.c Lffs.c
