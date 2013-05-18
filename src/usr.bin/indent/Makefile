# $MirOS: src/usr.bin/indent/Makefile,v 1.4 2009/05/16 14:09:06 tg Exp $
# $OpenBSD: Makefile,v 1.2 1996/06/26 05:34:27 deraadt Exp $

PROG=	indent
SRCS=	args.c indent.c io.c lexi.c parse.c pr_comment.c
CFLAGS+=-Wall

distribution:
	${INSTALL} -c -o root -g wheel -m 644 ${.CURDIR}/.indent.pro \
	    ${DESTDIR}/etc/skel/.indent.pro

.include <bsd.prog.mk>
