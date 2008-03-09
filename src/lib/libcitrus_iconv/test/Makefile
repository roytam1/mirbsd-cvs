# $MirOS: src/lib/libcitrus_iconv/test/Makefile,v 1.2 2006/02/01 14:40:14 tg Exp $

PROG=		iconv_test
NOMAN=		yes

test: .NOTMAIN all
	./${PROG}

.ifdef GNU
LDADD+=		-L/usr/mpkg/lib -lgiconv
CPPFLAGS+=	-Diconv=libiconv \
		-Diconv_open=libiconv_open \
		-Diconv_close=libiconv_close \
		-DGNU
.else
LDADD+=		-L/usr/lib -liconv
.endif

.include <bsd.prog.mk>
