# $MirOS: contrib/code/libhaible/Makefile,v 1.10 2006/05/30 12:58:52 tg Exp $

LIB=	haible
NOPIC=	Yes	# for now
SRCS+=	attribute.c
SRCS+=	iswctype.c
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

.include <bsd.lib.mk>
