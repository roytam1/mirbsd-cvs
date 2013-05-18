# $MirOS: contrib/code/libhaible/Makefile,v 1.28 2006/06/01 21:47:00 tg Exp $

LIB=	haible
NOPIC=	Yes	# for now
SRCS+=	attribute.c
SRCS+=	iswctype.c
SRCS+=	mblen.c
SRCS+=	mbrlen.c
SRCS+=	mbsrtowcs.c
SRCS+=	mbstowcs.c
SRCS+=	mbtowc.c
SRCS+=	tow_nop.c towl_tbl.c towu_tbl.c
SRCS+=	towctrans.c
SRCS+=	towlower.c
SRCS+=	towupper.c
SRCS+=	wcsrtombs.c
SRCS+=	wcstombs.c
SRCS+=	wcswidth.c
SRCS+=	wctomb.c
SRCS+=	wctrans.c
SRCS+=	wctype.c
SRCS+=	wcwidth.c

.PATH: ${.CURDIR}/string
SRCS+=	wcstok.c

# reachover for libc
.include <bsd.own.mk>
LIBCSRCDIR?=	${BSDSRCDIR}/lib/libc

.PATH: ${LIBCSRCDIR}/locale
CPPFLAGS+= -I${LIBCSRCDIR}/locale
SRCS+=	wcstod.c
SRCS+=	wcstol.c
SRCS+=	wcstoll.c
SRCS+=	wcstoul.c
SRCS+=	wcstoull.c

CFLAGS_wcstod.o+=	-Wno-cast-qual
CFLAGS_wcstol.o+=	-Wno-cast-qual
CFLAGS_wcstoll.o+=	-Wno-cast-qual
CFLAGS_wcstoul.o+=	-Wno-cast-qual
CFLAGS_wcstoull.o+=	-Wno-cast-qual

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
MAN+=		catgets.3
MLINKS+=	catgets.3 catopen.3
MLINKS+=	catgets.3 catclose.3

MAN+=		MB_CUR_MAX.3 wcswidth.3 wcwidth.3
MLINKS+=	MB_CUR_MAX.3 MB_LEN_MAX.3

# reachover for libc
.PATH: ${LIBCSRCDIR}/locale
MAN+=		iswctype.3 mbrlen.3 towctrans.3 wctrans.3 wctype.3
MAN+=		mbsrtowcs.3 wcsrtombs.3
MLINKS+=	iswalnum.3 iswblank.3 \
		iswalnum.3 iswcntrl.3 \
		iswalnum.3 iswdigit.3 \
		iswalnum.3 iswgraph.3 \
		iswalnum.3 iswprint.3 \
		iswalnum.3 iswpunct.3 \
		iswalnum.3 iswspace.3 \
		iswalnum.3 iswxdigit.3

.include <bsd.lib.mk>
