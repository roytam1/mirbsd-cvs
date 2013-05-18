# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.9 2006/05/26 13:52:06 tg Exp $

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
