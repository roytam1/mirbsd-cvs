# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.5 2005/09/30 21:45:26 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n

SRCS+=	btowc.c
SRCS+=	catalogues.c
SRCS+=	charsets.c
SRCS+=	isutf8.c
SRCS+=	langinfo.c
SRCS+=	mbrtowc.c
SRCS+=	wcrtomb.c
SRCS+=	wctob.c
