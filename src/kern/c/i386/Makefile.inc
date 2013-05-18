# $MirOS: src/kern/c/i386/Makefile.inc,v 1.5 2008/08/01 16:45:04 tg Exp $

SRCS+=		htonl.S htons.S
LSRCS+=		htonl.c htons.c ntohl.c ntohs.c

SRCS+=		strlen.S
UIF_KUSRCS+=	wcslen.S strlen.S -DWIDEC
LSRCS+=		strlen.c
UIF_LSRCS+=	wcslen.c strlen.c -DWIDEC

SRCS+=		divsi3.S udivsi3.S

SRCS+=		bzero.S ffs.S memchr.S memcmp.S memset.S strcmp.S
LSRCS+=		memchr.c memcmp.c memset.c strcmp.c
UIF_LSRCS+=	bcmp.c memcmp.c -DL_bcmp
UIF_LSRCS+=	strcoll.c strcmp.c -DL_strcoll
LSRCS+=		Lbzero.c Lffs.c
