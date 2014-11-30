# $MirOS: src/lib/libc/string/Makefile.inc,v 1.28 2011/10/16 20:54:58 tg Exp $
# $OpenBSD: Makefile.inc,v 1.17 2005/05/26 12:56:01 otto Exp $

# string sources
.PATH: ${LIBCSRCDIR}/arch/${MACHINE_ARCH}/string ${LIBCSRCDIR}/string

SRCS+=	bm.c memccpy.c strcasestr.c strdup.c \
	strerror.c strerror_r.c strmode.c strsignal.c strtok.c \
	wcscat.c wcschr.c wcscpy.c wcscspn.c \
	wcsncat.c wcsncmp.c wcsncpy.c wcspbrk.c wcsrchr.c wcsspn.c \
	wcsstr.c wmemchr.c wmemcmp.c wmemcpy.c \
	wmemmove.c wmemset.c
SRCS+=	stpcpy.c stpncpy.c

SRCS+=	wcsdup.c
SRCS+=	wcstok.c

.ifdef __CRAZY
CFLAGS_strcasestr.o+= -Wno-cast-qual
CFLAGS_strerror_r.o+= -Wno-error
CFLAGS_strpbrk.o+= -Wno-cast-qual
CFLAGS_strstr.o+= -Wno-cast-qual
CFLAGS_wcschr.o+= -Wno-cast-qual
CFLAGS_wcspbrk.o+= -Wno-cast-qual
CFLAGS_wcsrchr.o+= -Wno-cast-qual
CFLAGS_wcsstr.o+= -Wno-cast-qual
CFLAGS_wcswcs.o+= -Wno-cast-qual
CFLAGS_wmemchr.o+= -Wno-cast-qual
.endif

UIF_NUSRCS+=	wcswcs.c wcsstr.c -DWCSWCS

SRCS+=		strndup.c
UIF_NUSRCS+=	wcsndup.c strndup.c -DWIDEC

SRCS+=		strnlen.c
SRCS+=		timingsafe_bcmp.c
SRCS+=		timingsafe_memcmp.c

# machine-dependent net sources
# m-d Makefile.inc must include sources for:
#	bcopy()
#	strcat() strcpy() strcspn()
#	strncat() strpbrk() strsep()
#	strspn() strstr() swav()
# m-d Makefile.inc may include sources for:
#	memcpy() memmove()

.include "${LIBCSRCDIR}/arch/${MACHINE_ARCH}/string/Makefile.inc"

MAN+=	bm.3 bcmp.3 bcopy.3 bstring.3 bzero.3 ffs.3 memccpy.3 memchr.3 \
	memcmp.3 memcpy.3 memmove.3 memset.3 strcasecmp.3 strcat.3 \
	strchr.3 strcmp.3 strcoll.3 strcpy.3 strcspn.3 strerror.3 \
	string.3 strlen.3 strmode.3 strdup.3 strpbrk.3 strrchr.3 strsep.3 \
	strsignal.3 strspn.3 strstr.3 strtok.3 strxfrm.3 swab.3 strlcpy.3 \
	timingsafe_bcmp.3 wcstok.3 wmemchr.3

MLINKS+=bm.3 bm_comp.3 bm.3 bm_exec.3 bm.3 bm_free.3
MLINKS+=strchr.3 index.3
MLINKS+=strdup.3 strndup.3
MLINKS+=strrchr.3 rindex.3
MLINKS+=strcasecmp.3 strncasecmp.3
MLINKS+=strcat.3 strncat.3
MLINKS+=strcmp.3 strncmp.3
MLINKS+=strcpy.3 strncpy.3
MLINKS+=strlcpy.3 strlcat.3
MLINKS+=strlen.3 strnlen.3
MLINKS+=strstr.3 strcasestr.3
MLINKS+=strtok.3 strtok_r.3
MLINKS+=strerror.3 strerror_r.3
MLINKS+=timingsafe_bcmp.3 timingsafe_memcmp.3
MLINKS+=wmemchr.3 wcscasecmp.3
MLINKS+=wmemchr.3 wcscat.3
MLINKS+=wmemchr.3 wcschr.3
MLINKS+=wmemchr.3 wcscmp.3
MLINKS+=wmemchr.3 wcscoll.3
MLINKS+=wmemchr.3 wcscpy.3
MLINKS+=wmemchr.3 wcscspn.3
MLINKS+=wmemchr.3 wcsdup.3
MLINKS+=wmemchr.3 wcsftime.3
MLINKS+=wmemchr.3 wcslcat.3
MLINKS+=wmemchr.3 wcslcpy.3
MLINKS+=wmemchr.3 wcslen.3
MLINKS+=wmemchr.3 wcsncasecmp.3
MLINKS+=wmemchr.3 wcsncat.3
MLINKS+=wmemchr.3 wcsncmp.3
MLINKS+=wmemchr.3 wcsncpy.3
MLINKS+=wmemchr.3 wcsndup.3
MLINKS+=wmemchr.3 wcspbrk.3
MLINKS+=wmemchr.3 wcsrchr.3
MLINKS+=wmemchr.3 wcsspn.3
MLINKS+=wmemchr.3 wcsstr.3
MLINKS+=wmemchr.3 wcswcs.3
MLINKS+=wmemchr.3 wcsxfrm.3
MLINKS+=wmemchr.3 wmemcmp.3
MLINKS+=wmemchr.3 wmemcpy.3
MLINKS+=wmemchr.3 wmemmove.3
MLINKS+=wmemchr.3 wmemset.3
