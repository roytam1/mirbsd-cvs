# $MirOS$

PROG=		figlet
SRCS=		crc.c figlet.c inflate.c zipio.c
MAN=		${PROG}.6

CPPFLAGS+=	-DDEFAULTFONTDIR=\"${TRUEPREFIX}/share/figlet\"
CPPFLAGS+=	-DDEFAULTFONTFILE=\"standard.flf\"

.PATH: ${.CURDIR}/..

.include <bsd.prog.mk>
