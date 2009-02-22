# $MirOS: src/libexec/cprng/Makefile,v 1.4 2008/12/27 22:15:30 tg Exp $

PROG=		tpmrng
MAN=		tpmrng.8
LDSTATIC=	-static
LDFLAGS+=	-Wl,-n -Wl,-s

${PROG}: ${CRTI} ${CRTBEGIN} ${LIBCRT0} ${OBJS} ${LIBC} ${DPADD} ${CRTEND} ${CRTN}
	${LINK.prog} -o $@
	${STRIP} --strip-unneeded -s -R .comment ${PROG}

.include <bsd.prog.mk>
