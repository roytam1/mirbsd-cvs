# $MirOS: src/lib/libc/i18n/Makefile.inc,v 1.37 2011/10/16 20:54:57 tg Exp $

.PATH: ${LIBCSRCDIR}/i18n
.PATH: ${LIBCSRCDIR}/locale

CLEANFILES+=	${MIRI18N_GEND}

SRCS+=	${MIRI18N_GEND}
SRCS+=	tbl_att0.c
SRCS+=	tbl_attr.c
SRCS+=	tbl_towl.c
SRCS+=	tbl_towt.c
SRCS+=	tbl_towu.c
SRCS+=	tbl_wnop.c

SRCS+=	catalogues.c
SRCS+=	charsets.c
SRCS+=	langinfo.c
SRCS+=	mbcurmax.c

SRCS+=	btowc.c
SRCS+=	iswctype.c
SRCS+=	mblen.c
SRCS+=	mbrlen.c
SRCS+=	mbrtowc.c
SRCS+=	mbsinit.c
SRCS+=	mbslen.c
SRCS+=	mbsrtowcs.c
SRCS+=	mbstowcs.c
SRCS+=	mbtowc.c
SRCS+=	towctrans.c
SRCS+=	wcsftime.c
SRCS+=	wcsrtombs.c
SRCS+=	wcstombs.c
SRCS+=	wcswidth.c
SRCS+=	wctob.c
SRCS+=	wctomb.c
SRCS+=	wctrans.c
SRCS+=	wctype.c
SRCS+=	wcwidth.c

UIF_NUSRCS+=	mbsnrtowcs.c mbsrtowcs.c -DMBSNRTOWCS
UIF_NUSRCS+=	wcsnrtombs.c wcsrtombs.c -DWCSNRTOMBS

.for _i in alnum alpha blank cntrl digit graph lower print punct space \
    title upper xdigit
MIRI18N_GEND+=	isw${_i}.c

isw${_i}.c: iswTYPE.c
	sed 's!@@TYPE@@!${_i}!g' <$> >$@
.endfor

.for _i in lower upper
MIRI18N_GEND+=	tow${_i}.c

tow${_i}.c: towTYPE.c
	sed 's!@@TYPE@@!${_i}!g' <$> >$@
.endfor

SRCS+=	towtitle.c

MAN+=	catgets.3
MLINKS+=catgets.3 catopen.3
MLINKS+=catgets.3 catclose.3

# from ../locale/
CPPFLAGS+= -I${LIBCSRCDIR}/locale

SRCS+=	wcstod.c
SRCS+=	wcstol.c
SRCS+=	wcstoll.c
SRCS+=	wcstoul.c
SRCS+=	wcstoull.c

.ifdef __CRAZY
CFLAGS_wcstod.o+=	-Wno-cast-qual
CFLAGS_wcstol.o+=	-Wno-cast-qual
CFLAGS_wcstoll.o+=	-Wno-cast-qual
CFLAGS_wcstoul.o+=	-Wno-cast-qual
CFLAGS_wcstoull.o+=	-Wno-cast-qual
.endif

MAN+=	btowc.3
MAN+=	iswalnum.3
MAN+=	iswctype.3
MAN+=	iswoctet.3
MAN+=	mblen.3
MAN+=	mbrlen.3
MAN+=	mbrtowc.3
MAN+=	mbsinit.3
MAN+=	mbsrtowcs.3
MAN+=	mbstowcs.3
MAN+=	mbtowc.3
MAN+=	nl_langinfo.3
MAN+=	optu8to16.3
MAN+=	setlocale.3
MAN+=	towctrans.3
MAN+=	towlower.3
MAN+=	wcrtomb.3
MAN+=	wcsrtombs.3
MAN+=	wcstombs.3
MAN+=	wctob.3
MAN+=	wctomb.3
MAN+=	wctrans.3
MAN+=	wctype.3
MLINKS+=iswalnum.3 iswalpha.3
MLINKS+=iswalnum.3 iswblank.3
MLINKS+=iswalnum.3 iswcntrl.3
MLINKS+=iswalnum.3 iswdigit.3
MLINKS+=iswalnum.3 iswgraph.3
MLINKS+=iswalnum.3 iswlower.3
MLINKS+=iswalnum.3 iswprint.3
MLINKS+=iswalnum.3 iswpunct.3
MLINKS+=iswalnum.3 iswspace.3
MLINKS+=iswalnum.3 iswupper.3
MLINKS+=iswalnum.3 iswxdigit.3
MLINKS+=setlocale.3 localeconv.3
MLINKS+=towlower.3 towupper.3
MLINKS+=mbsrtowcs.3 mbsnrtowcs.3
MLINKS+=mbsrtowcs.3 mbsnrtowcsvis.3
MLINKS+=optu8to16.3 optu8to16vis.3
MLINKS+=wcrtomb.3 optu16to8.3
MLINKS+=wcsrtombs.3 wcsnrtombs.3

beforedepend: ${MIRI18N_GEND}
