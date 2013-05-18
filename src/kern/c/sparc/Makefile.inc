# $MirOS: src/kern/c/sparc/Makefile.inc,v 1.3 2007/02/07 02:29:37 tg Exp $

SRCS+=		htonl.c htons.c ntohl.c ntohs.c

SRCS+=		strlen.S
LSRCS+=		strlen.c
UIF_KUSRCS+=	wcslen.c strlen.c -DWIDEC

SRCS+=		bzero.S ffs.S memchr.c memcmp.c memset.c strcmp.c
UNIFDEF_SRCS+=	bcmp.c memcmp.c -DL_bcmp
UNIFDEF_SRCS+=	strcoll.c strcmp.c -DL_strcoll
LSRCS+=		Lbzero.c Lffs.c
