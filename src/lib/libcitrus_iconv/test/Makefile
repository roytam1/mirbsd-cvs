# $MirOS$

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
LDADD+=		-lcitrus_iconv
.endif

.include <bsd.prog.mk>
