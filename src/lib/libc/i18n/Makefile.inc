# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.6 2005/09/30 22:13:55 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n

SRCS+=	btowc.c
SRCS+=	catalogues.c
SRCS+=	charsets.c
SRCS+=	isutf8.c
SRCS+=	langinfo.c
SRCS+=	mbrtowc.c
SRCS+=	wcrtomb.c
SRCS+=	wctob.c

SRCS+=	multibyte.c
