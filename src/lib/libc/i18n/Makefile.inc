# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.10 2006/06/01 21:58:12 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n

# for OpenBSD's manual pages and strto<num> sources
.include "${LIBCSRCDIR}/locale/Makefile.inc"

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
