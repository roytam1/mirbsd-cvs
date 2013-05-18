# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.8 2006/01/30 13:01:44 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n

# for OpenBSD's manual pages
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
