# $MirOS: src/libexec/cprng/Makefile,v 1.2 2007/08/25 10:53:09 tg Exp $

PROG=		cprng
MAN=		cprng.8
LDSTATIC=	-static
LDFLAGS+=	-Wl,-n -Wl,-s

${PROG}: ${CRTI} ${CRTBEGIN} ${LIBCRT0} ${OBJS} ${LIBC} ${DPADD} ${CRTEND} ${CRTN}
	${LINK.prog} -o $@
	${STRIP} --strip-unneeded -s ${PROG}

.include <bsd.prog.mk>
