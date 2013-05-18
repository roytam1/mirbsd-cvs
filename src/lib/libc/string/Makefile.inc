# $MirOS: src/lib/libc/string/Makefile.inc,v 1.14 2006/11/21 01:04:09 tg Exp $
# $OpenBSD: Makefile.inc,v 1.17 2005/05/26 12:56:01 otto Exp $

# string sources
.PATH: ${LIBCSRCDIR}/arch/${MACHINE_ARCH}/string ${LIBCSRCDIR}/string

SRCS+=	bm.c memccpy.c strcasestr.c strdup.c \
	strerror.c strerror_r.c strmode.c strsignal.c strtok.c \
	strxfrm.c strlcat.c strlcpy.c \
	wcscat.c wcschr.c wcscmp.c wcscpy.c wcscspn.c wcslcat.c wcslcpy.c \
	wcslen.c wcsncat.c wcsncmp.c wcsncpy.c wcspbrk.c wcsrchr.c wcsspn.c \
	wcsstr.c wcswcs.c wmemchr.c wmemcmp.c wmemcpy.c \
	wmemmove.c wmemset.c

SRCS+=	wcsdup.c
SRCS+=	wcstok.c
SRCS+=	wcsxfrm.c

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

UNIFDEF_SRCS+=	strlcpy.c strlfun.c HAVE_STRLCAT=1
UNIFDEF_SRCS+=	strlcat.c strlfun.c HAVE_STRLCPY=1
UNIFDEF_SRCS+=	wcslcpy.c wcslfun.c HAVE_WCSLCAT=1
UNIFDEF_SRCS+=	wcslcat.c wcslfun.c HAVE_WCSLCPY=1

UNIFDEF_SRCS+=	strcasecmp.c strcasecmpfun.c STRCASECMP
UNIFDEF_SRCS+=	strncasecmp.c strcasecmpfun.c STRNCASECMP
UNIFDEF_SRCS+=	wcscasecmp.c strcasecmpfun.c WCSCASECMP
UNIFDEF_SRCS+=	wcsncasecmp.c strcasecmpfun.c WCSNCASECMP

UNIFDEF_SRCS+=	strcoll.c strcmp.c STRCOLL
UNIFDEF_SRCS+=	wcscoll.c wcscmp.c WCSCOLL
UNIFDEF_SRCS+=	wcswcs.c wcsstr.c WCSWCS

# machine-dependent net sources
# m-d Makefile.inc must include sources for:
#	bcopy() bzero() ffs() index() memchr() memcmp() memset()
#	rindex() strcat() strcmp() strcpy() strcspn() strlen()
#	strncat() strncmp() strncpy() strpbrk() strsep()
#	strspn() strstr() swav()
# m-d Makefile.inc may include sources for:
#	bcmp() memcpy() memmove() strchr() strrchr()

.include "${LIBCSRCDIR}/arch/${MACHINE_ARCH}/string/Makefile.inc"

# if no machine specific bcmp(3), build one out of memcmp(3).
.ifndef _MD_BCMP
UNIFDEF_SRCS+=	bcmp.c memcmp.c BCMP
.else
LOBJS+=		bcmp.ln

bcmp.ln: memcmp.c
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i \
	    -DBCMP -o $@ $>
.endif

# if no machine specific memmove(3), build one out of bcopy(3).
.ifndef _MD_MEMMOVE
UNIFDEF_SRCS+=	memmove.c bcopy.c MEMMOVE
.else
LOBJS+=		memmove.ln

memmove.ln: bcopy.c
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i \
	    -DMEMMOVE -o $@ $>
.endif

# if no machine specific memcpy(3), build one out of bcopy(3).
# if there is a machine specific memmove(3), we'll assume it aliases
# memcpy(3).
.if !defined(_MD_MEMCPY) && !defined(_MD_MEMMOVE)
UNIFDEF_SRCS+=	memcpy.c bcopy.c MEMCOPY
.else
LOBJS+=		memcpy.ln

memcpy.ln: bcopy.c
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i \
	    -DMEMCOPY -o $@ $>
.endif

# if no machine specific strchr(3), build one out of index(3).
.ifndef _MD_STRCHR
UNIFDEF_SRCS+=	strchr.c index.c STRCHR
.else
LOBJS+=		strchr.ln

strchr.ln: index.c
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i \
	    -DSTRCHR -o $@ $>
.endif

# if no machine specific strrchr(3), build one out of rindex(3).
.ifndef _MD_STRRCHR
UNIFDEF_SRCS+=	strrchr.c rindex.c STRRCHR
.else
LOBJS+=		strrchr.ln

strrchr.ln: rindex.c
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i \
	    -DSTRRCHR -o $@ $>
.endif

MAN+=	bm.3 bcmp.3 bcopy.3 bstring.3 bzero.3 ffs.3 memccpy.3 memchr.3 \
	memcmp.3 memcpy.3 memmove.3 memset.3 strcasecmp.3 strcat.3 \
	strchr.3 strcmp.3 strcoll.3 strcpy.3 strcspn.3 strerror.3 \
	string.3 strlen.3 strmode.3 strdup.3 strpbrk.3 strrchr.3 strsep.3 \
	strsignal.3 strspn.3 strstr.3 strtok.3 strxfrm.3 swab.3 strlcpy.3 \
	wcstok.3 wmemchr.3

MLINKS+=bm.3 bm_comp.3 bm.3 bm_exec.3 bm.3 bm_free.3
MLINKS+=strchr.3 index.3
MLINKS+=strrchr.3 rindex.3
MLINKS+=strcasecmp.3 strncasecmp.3
MLINKS+=strcat.3 strncat.3
MLINKS+=strcmp.3 strncmp.3
MLINKS+=strcpy.3 strncpy.3
MLINKS+=strlcpy.3 strlcat.3
MLINKS+=strstr.3 strcasestr.3
MLINKS+=strtok.3 strtok_r.3
MLINKS+=strerror.3 strerror_r.3
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
