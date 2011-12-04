# $MirOS: src/lib/libc/string/Makefile.inc,v 1.3 2005/04/16 20:30:49 tg Exp $
# $OpenBSD: Makefile.inc,v 1.14 2005/03/30 03:04:19 deraadt Exp $

# string sources
.PATH: ${LIBCSRCDIR}/arch/${MACHINE_ARCH}/string ${LIBCSRCDIR}/string

SRCS+=	bm.c memccpy.c strcasecmp.c strcasestr.c strcoll.c strdup.c \
	strerror.c strerror_r.c strlfun.c strmode.c strsignal.c strtok.c \
	strxfrm.c __strsignal.c

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
SRCS+=		bcmp.c
CLEANFILES+=	bcmp.c

bcmp.c: memcmp.c
	unifdef -DBCMP $> >$@
.else
LOBJS+=		bcmp.ln

bcmp.ln: memcmp.c
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i \
	    -DBCMP -o $@ $>
.endif

# if no machine specific memmove(3), build one out of bcopy(3).
.ifndef _MD_MEMMOVE
SRCS+=		memmove.c
CLEANFILES+=	memmove.c

memmove.c: bcopy.c
	unifdef -DMEMMOVE -UMEMCOPY $> >$@
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
SRCS+=		memcpy.c
CLEANFILES+=	memcpy.c

memcpy.c: bcopy.c
	unifdef -UMEMMOVE -DMEMCOPY $> >$@
.else
LOBJS+=		memcpy.ln

memcpy.ln: bcopy.c
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i \
	    -DMEMCOPY -o $@ $>
.endif

# if no machine specific strchr(3), build one out of index(3).
.ifndef _MD_STRCHR
SRCS+=		strchr.c
CLEANFILES+=	strchr.c

strchr.c: index.c
	unifdef -DSTRCHR $> >$@
.else
LOBJS+=		strchr.ln

strchr.ln: index.c
	${LINT} ${LINTFLAGS} ${CFLAGS:M-[IDU]*} ${CPPFLAGS:M-[IDU]*} -i \
	    -DSTRCHR -o $@ $>
.endif

# if no machine specific strrchr(3), build one out of rindex(3).
.ifndef _MD_STRRCHR
SRCS+=		strrchr.c
CLEANFILES+=	strrchr.c

strrchr.c: rindex.c
	unifdef -DSTRRCHR $> >$@
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
	strsignal.3 strspn.3 strstr.3 strtok.3 strxfrm.3 swab.3 strlcpy.3

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
