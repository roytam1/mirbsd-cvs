# $MirOS: src/gnu/usr.bin/rcs/getdate/Makefile,v 1.4 2016/10/21 21:21:38 tg Exp $

PROG=		getdate
NOMAN=		yes
CPPFLAGS+=	-DTEST

NEED_RCS_LIB=	No
.include "../Makefile.inc"

CPPFLAGS+=	-I${CVSLIB}
.PATH: ${CVSLIB}

# see mircvs://contrib/code/Snippets/posixtz.c
.if exists(/usr/lib/libposixtz.so)
REGRESS_ENV+=	GETDATE_LD_PRELOAD=/usr/lib/libposixtz.so
.endif

CLEANFILES+=	getdate-expected getdate-got getdate.cmp getdate.log*

check:
	(set +e; env ${REGRESS_ENV} ${SHELL} ${CVSLIB}/test-getdate.sh; \
	    rv=$$?; cat getdate.log; exit $$rv)
	@echo all OK

.include <bsd.prog.mk>
