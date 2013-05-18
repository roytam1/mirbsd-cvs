# $MirOS: src/kern/c/i386/Makefile.inc,v 1.3 2007/02/06 16:28:38 tg Exp $

SRCS+=		htonl.S htons.S
LSRCS+=		htonl.c htons.c ntohl.c ntohs.c

SRCS+=		strlen.S
UIF_KUSRCS+=	wcslen.S strlen.S -DWIDEC
LSRCS+=		strlen.c
UIF_LSRCS+=	wcslen.c strlen.c -DWIDEC
