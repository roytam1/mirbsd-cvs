# $MirOS: src/lib/libc/locale/Makefile.inc,v 1.5 2006/06/01 21:58:13 tg Exp $
# $OpenBSD: Makefile.inc,v 1.10 2005/08/08 05:53:01 espie Exp $

.ifdef __LIBC_OPENBSD_LOCALE
# locale sources
.PATH: ${LIBCSRCDIR}/arch/${MACHINE_ARCH}/locale ${LIBCSRCDIR}/locale

SRCS+=	_def_messages.c _def_monetary.c _def_numeric.c _def_time.c \
	localeconv.c nl_langinfo.c setlocale.c iswctype.c mbrtowc_sb.c \
	multibyte_sb.c \
	__mb_cur_max.c wcstod.c wcstol.c wcstoul.c wcstoll.c wcstoull.c \
	setrunelocale.c runeglue.c rune.c runetable.c ___runetype_mb.c \
	_wctrans.c

MAN+=	nl_langinfo.3 setlocale.3 iswalnum.3 towlower.3 \
	btowc.3 mblen.3 mbrlen.3 mbrtowc.3 mbsinit.3 mbsrtowcs.3 \
	mbstowcs.3 mbtowc.3 wcrtomb.3 wcsrtombs.3 wcstombs.3 wctob.3 \
	wctomb.3 wctype.3 iswctype.3 wctrans.3 towctrans.3
MLINKS+=setlocale.3 localeconv.3 \
	iswalnum.3 iswalpha.3 \
	iswalnum.3 iswblank.3 \
	iswalnum.3 iswcntrl.3 \
	iswalnum.3 iswdigit.3 \
	iswalnum.3 iswgraph.3 \
	iswalnum.3 iswlower.3 \
	iswalnum.3 iswprint.3 \
	iswalnum.3 iswpunct.3 \
	iswalnum.3 iswspace.3 \
	iswalnum.3 iswupper.3 \
	iswalnum.3 iswxdigit.3 \
	towlower.3 towupper.3

CFLAGS+=-I${.CURDIR}
.else

.PATH: ${LIBCSRCDIR}/locale
CPPFLAGS+= -I${LIBCSRCDIR}/locale

SRCS+=	wcstod.c
SRCS+=	wcstol.c
SRCS+=	wcstoll.c
SRCS+=	wcstoul.c
SRCS+=	wcstoull.c

CFLAGS_wcstod.o+=	-Wno-cast-qual
CFLAGS_wcstol.o+=	-Wno-cast-qual
CFLAGS_wcstoll.o+=	-Wno-cast-qual
CFLAGS_wcstoul.o+=	-Wno-cast-qual
CFLAGS_wcstoull.o+=	-Wno-cast-qual

MAN+=	btowc.3
MAN+=	mblen.3
MAN+=	mbrlen.3
MAN+=	mbrtowc.3
MAN+=	mbsinit.3
MAN+=	mbsrtowcs.3
MAN+=	mbstowcs.3
MAN+=	mbtowc.3
MAN+=	nl_langinfo.3
MAN+=	setlocale.3
MAN+=	wcrtomb.3
MAN+=	wcsrtombs.3
MAN+=	wcstombs.3
MAN+=	wctob.3
MAN+=	wctomb.3
MAN+=	wctrans.3
MAN+=	wctype.3
MLINKS+=setlocale.3 localeconv.3

# stubs
MAN+=	iswalnum.3 towlower.3
MLINKS+=iswalnum.3 iswalpha.3
MLINKS+=iswalnum.3 iswlower.3
MLINKS+=iswalnum.3 iswupper.3
MLINKS+=towlower.3 towupper.3

.endif
