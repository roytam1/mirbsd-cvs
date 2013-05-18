# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.4 2005/09/22 21:48:02 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n

SRCS+=	btowc.c
SRCS+=	catalogues.c
SRCS+=	charsets.c
SRCS+=	isutf8.c
SRCS+=	langinfo.c
SRCS+=	mbcurmax.c
SRCS+=	mbrtowc.c
SRCS+=	wcrtomb.c
SRCS+=	wctob.c
