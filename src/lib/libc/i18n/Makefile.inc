# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.11 2006/06/01 21:59:49 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n

# for OpenBSD's manual pages and strto<num> sources
.include "${LIBCSRCDIR}/locale/Makefile.inc"

SRCS+=	tbl_attr.c
SRCS+=	tbl_towl.c
SRCS+=	tbl_towu.c
SRCS+=	tbl_wnop.c

SRCS+=	btowc.c
SRCS+=	catalogues.c
SRCS+=	charsets.c
SRCS+=	isutf8.c
SRCS+=	langinfo.c
SRCS+=	mbrtowc.c
SRCS+=	mbsinit.c
SRCS+=	wcrtomb.c
SRCS+=	wctob.c

SRCS+=	multibyte.c

MAN+=	catgets.3
MLINKS+=catgets.3 catopen.3
MLINKS+=catgets.3 catclose.3
