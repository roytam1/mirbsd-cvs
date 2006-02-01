# $MirOS: src/lib/libcitrus_iconv/test/Makefile,v 1.1 2006/01/31 19:13:45 tg Exp $

PROG=		iconv_test
NOMAN=		yes

test: .NOTMAIN all
	./${PROG}

.ifdef GNU
LDADD+=		-L/usr/mpkg/lib -liconv
CPPFLAGS+=	-Diconv=libiconv \
		-Diconv_open=libiconv_open \
		-Diconv_close=libiconv_close
.else
LDADD+=		-L/usr/lib -liconv
.endif

.include <bsd.prog.mk>
