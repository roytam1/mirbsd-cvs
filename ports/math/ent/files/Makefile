# $MirOS$

PROG=	ent
SRCS=	ent.c iso8859.c randtest.c
NOMAN=	yes

BINDIR?=${TRUEPREFIX}/bin
LDADD+=	-lm
DPADD+=	${LIBM}

regress: ${PROG}
	cd ${.CURDIR} && (PATH=. ${SHELL} entest.bat) \
	    && diff -du entest.mas entest.bak

beforeinstall:
	${BSD_INSTALL_DATA_DIR} ${PREFIX}/share/doc/ent
	${BSD_INSTALL_DATA} ent.html entitle.gif ${PREFIX}/share/doc/ent/

.include <bsd.prog.mk>
