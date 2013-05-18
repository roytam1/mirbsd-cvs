# $MirOS: src/libexec/cprng/Makefile,v 1.3 2007/09/28 20:05:25 tg Exp $

PROG=		cprng
MAN=		cprng.8
LDSTATIC=	-static
LDFLAGS+=	-Wl,-n -Wl,-s

${PROG}: ${CRTI} ${CRTBEGIN} ${LIBCRT0} ${OBJS} ${LIBC} ${DPADD} ${CRTEND} ${CRTN}
	${LINK.prog} -o $@
	${STRIP} --strip-unneeded -s -R .comment ${PROG}

.include <bsd.prog.mk>
