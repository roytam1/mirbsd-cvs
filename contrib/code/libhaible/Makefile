# $MirOS: contrib/code/libhaible/Makefile,v 1.36 2006/06/01 22:47:36 tg Exp $

LIB=	haible
NOPIC=	Yes	# for now

.PATH: ${.CURDIR}/string
SRCS+=	wcstok.c

# for "miri18n.h"
CPPFLAGS+= -I${LIBCSRCDIR}/include

# missing
#SRCS+=	fwprintf.c
#SRCS+=	fwscanf.c
#SRCS+=	swprintf.c
#SRCS+=	swscanf.c
#SRCS+=	vfwprintf.c
#SRCS+=	vfwscanf.c
#SRCS+=	vswprintf.c
#SRCS+=	vswscanf.c
#SRCS+=	vwprintf.c
#SRCS+=	vwscanf.c
#SRCS+=	wcsftime.c
#SRCS+=	wprintf.c
#SRCS+=	wscanf.c

# manual pages
MAN+=		MB_CUR_MAX.3 wcswidth.3 wcwidth.3
MLINKS+=	MB_CUR_MAX.3 MB_LEN_MAX.3

.include <bsd.lib.mk>
