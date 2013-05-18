# $MirOS: src/kern/c/sparc/Makefile.inc,v 1.2 2007/02/06 16:28:38 tg Exp $

SRCS+=		htonl.c htons.c ntohl.c ntohs.c

SRCS+=		strlen.S
LSRCS+=		strlen.c
UIF_KUSRCS+=	wcslen.c strlen.c -DWIDEC
