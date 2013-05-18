# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.7 2005/10/11 21:58:33 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n

# for OpenBSD's manual pages
.include "${LIBCSRCDIR}/locale/Makefile.inc"

SRCS+=	btowc.c
SRCS+=	catalogues.c
SRCS+=	charsets.c
SRCS+=	isutf8.c
SRCS+=	langinfo.c
SRCS+=	mbrtowc.c
SRCS+=	wcrtomb.c
SRCS+=	wctob.c

SRCS+=	multibyte.c
