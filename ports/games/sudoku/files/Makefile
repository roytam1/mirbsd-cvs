# $MirOS$

PROG=		sudoku
SRCS=		sudoku.c
MAN=		sudoku.6

LDADD+=		-lcurses
CPPFLAGS+=	-DTEMPLATE=\"${PREFIX}/share/sudoku/template\" \
		-DPRECANNED=\"${PREFIX}/share/sudoku/precanned\"

.include <bsd.prog.mk>
