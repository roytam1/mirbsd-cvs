# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.13 2006/06/01 22:17:20 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n

# for OpenBSD's manual pages and strto<num> sources
.include "${LIBCSRCDIR}/locale/Makefile.inc"

CLEANFILES+=	${MIRI18N_GEND}

SRCS+=	${MIRI18N_GEND}
SRCS+=	tbl_attr.c
SRCS+=	tbl_towl.c
SRCS+=	tbl_towu.c
SRCS+=	tbl_wnop.c

SRCS+=	catalogues.c
SRCS+=	charsets.c
SRCS+=	isutf8.c
SRCS+=	langinfo.c

SRCS+=	btowc.c
SRCS+=	mblen.c
SRCS+=	mbrlen.c
SRCS+=	mbrtowc.c
SRCS+=	mbsinit.c
SRCS+=	mbsrtowcs.c
SRCS+=	mbstowcs.c
SRCS+=	mbtowc.c
SRCS+=	wcrtomb.c
SRCS+=	wcsrtombs.c
SRCS+=	wcstombs.c
SRCS+=	wcswidth.c
SRCS+=	wctob.c
SRCS+=	wctomb.c
SRCS+=	wctrans.c
SRCS+=	wctype.c
SRCS+=	wcwidth.c

SRCS+=	multibyte.c

.for _i in alnum alpha blank cntrl digit graph lower print punct space upper \
    xdigit
MIRI18N_GEND+=	isw${_i}.c

isw${_i}.c: iswTYPE.c
	sed 's!@@TYPE@@!${_i}!g' <$> >$@
.endfor

MAN+=	catgets.3
MLINKS+=catgets.3 catopen.3
MLINKS+=catgets.3 catclose.3

beforedepend: ${MIRI18N_GEND}
