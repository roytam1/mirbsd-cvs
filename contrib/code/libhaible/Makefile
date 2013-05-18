# $MirOS: contrib/code/libhaible/Makefile,v 1.18 2006/05/30 18:41:53 tg Exp $

LIB=	haible
NOPIC=	Yes	# for now
SRCS+=	attribute.c
SRCS+=	iswctype.c
SRCS+=	mblen.c
SRCS+=	mbrlen.c
SRCS+=	mbstowcs.c
SRCS+=	mbtowc.c
SRCS+=	tow_nop.c
SRCS+=	towctrans.c
SRCS+=	towlower.c
SRCS+=	towupper.c
SRCS+=	wcscasecmp.c
SRCS+=	wcsncasecmp.c
SRCS+=	wcswidth.c
SRCS+=	wctrans.c
SRCS+=	wctype.c
SRCS+=	wcwidth.c

.PATH: ${.CURDIR}/string
SRCS+=	wcsdup.c
SRCS+=	wcstok.c

# missing
#SRCS+=	fwprintf.c
#SRCS+=	fwscanf.c
#SRCS+=	mbrlen.c
#SRCS+=	mbsrtowcs.c
#SRCS+=	swprintf.c
#SRCS+=	swscanf.c
#SRCS+=	vfwprintf.c
#SRCS+=	vfwscanf.c
#SRCS+=	vswprintf.c
#SRCS+=	vswscanf.c
#SRCS+=	vwprintf.c
#SRCS+=	vwscanf.c
#SRCS+=	wcscoll.c
#SRCS+=	wcsftime.c
#SRCS+=	wcsrtombs.c
#SRCS+=	wcstod.c
#SRCS+=	wcstof.c
#SRCS+=	wcstol.c
#SRCS+=	wcstold.c
#SRCS+=	wcstoll.c
#SRCS+=	wcstoul.c
#SRCS+=	wcstoull.c
#SRCS+=	wcsxfrm.c
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

# reachover for libc
.include <bsd.own.mk>
LIBCSRCDIR?=	${BSDSRCDIR}/lib/libc

.PATH: ${LIBCSRCDIR}/locale
MAN+=		iswctype.3 mbrlen.3 towctrans.3 wctrans.3 wctype.3
# not yet
#MAN+=		mbsrtowcs.3 wcsrtombs.3
MLINKS+=	iswalnum.3 iswblank.3 \
		iswalnum.3 iswcntrl.3 \
		iswalnum.3 iswdigit.3 \
		iswalnum.3 iswgraph.3 \
		iswalnum.3 iswprint.3 \
		iswalnum.3 iswpunct.3 \
		iswalnum.3 iswspace.3 \
		iswalnum.3 iswxdigit.3

# changed wmemstr manual page. copied:
MAN+=		wmemchr.3
MLINKS+=wmemchr.3 wmemcmp.3
MLINKS+=wmemchr.3 wmemcpy.3
MLINKS+=wmemchr.3 wmemmove.3
MLINKS+=wmemchr.3 wmemset.3
MLINKS+=wmemchr.3 wcscat.3
MLINKS+=wmemchr.3 wcschr.3
MLINKS+=wmemchr.3 wcscmp.3
MLINKS+=wmemchr.3 wcscpy.3
MLINKS+=wmemchr.3 wcscspn.3
MLINKS+=wmemchr.3 wcslcat.3
MLINKS+=wmemchr.3 wcslcpy.3
MLINKS+=wmemchr.3 wcslen.3
MLINKS+=wmemchr.3 wcsncat.3
MLINKS+=wmemchr.3 wcsncmp.3
MLINKS+=wmemchr.3 wcsncpy.3
MLINKS+=wmemchr.3 wcspbrk.3
MLINKS+=wmemchr.3 wcsrchr.3
MLINKS+=wmemchr.3 wcsspn.3
MLINKS+=wmemchr.3 wcsstr.3
# added:
MLINKS+=wmemchr.3 wcscasecmp
MLINKS+=wmemchr.3 wcscoll
MLINKS+=wmemchr.3 wcsdup
MLINKS+=wmemchr.3 wcsftime
MLINKS+=wmemchr.3 wcsncasecmp
MLINKS+=wmemchr.3 wcswcs
MLINKS+=wmemchr.3 wcsxfrm

.include <bsd.lib.mk>
