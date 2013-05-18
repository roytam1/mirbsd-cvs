# $MirOS$

PROG=		cprng
NOMAN=		Yes
LDSTATIC=	-static
LDFLAGS+=	-Wl,-n -Wl,-s

${PROG}: ${CRTI} ${CRTBEGIN} ${LIBCRT0} ${OBJS} ${LIBC} ${DPADD} ${CRTEND} ${CRTN}
	${LINK.prog} -o $@
	${STRIP} --strip-unneeded -s -R .comment ${PROG}

.include <bsd.prog.mk>
