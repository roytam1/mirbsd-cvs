# $MirOS: contrib/code/libhaible/Makefile,v 1.32 2006/06/01 22:03:22 tg Exp $

LIB=	haible
NOPIC=	Yes	# for now
SRCS+=	iswctype.c
SRCS+=	towctrans.c
SRCS+=	towlower.c
SRCS+=	towupper.c

.PATH: ${.CURDIR}/string
SRCS+=	wcstok.c

# reachover for libc
.include <bsd.own.mk>
LIBCSRCDIR?=	${BSDSRCDIR}/lib/libc

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

.for _wctype in alnum alpha blank cntrl digit graph lower print punct \
    space upper xdigit
GENERATED+=	isw${_wctype}.c

isw${_wctype}.c: iswTYPE.c
	sed 's!TYPE!${_wctype}!g' <$> >$@
.endfor

SRCS+=	${GENERATED}

CLEANFILES+=	${GENERATED}

beforedepend: ${GENERATED}

# manual pages
MAN+=		MB_CUR_MAX.3 wcswidth.3 wcwidth.3
MLINKS+=	MB_CUR_MAX.3 MB_LEN_MAX.3

# reachover for libc
.PATH: ${LIBCSRCDIR}/locale
MAN+=		iswctype.3 towctrans.3
MLINKS+=	iswalnum.3 iswblank.3 \
		iswalnum.3 iswcntrl.3 \
		iswalnum.3 iswdigit.3 \
		iswalnum.3 iswgraph.3 \
		iswalnum.3 iswprint.3 \
		iswalnum.3 iswpunct.3 \
		iswalnum.3 iswspace.3 \
		iswalnum.3 iswxdigit.3

.include <bsd.lib.mk>
