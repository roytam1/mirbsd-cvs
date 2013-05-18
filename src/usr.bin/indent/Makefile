# $MirOS: src/usr.bin/indent/Makefile,v 1.3 2005/03/15 19:23:51 tg Exp $
# $OpenBSD: Makefile,v 1.2 1996/06/26 05:34:27 deraadt Exp $

PROG=	indent
SRCS=	args.c indent.c io.c lexi.c parse.c pr_comment.c
CFLAGS+=-Wall

distribution:
	${INSTALL} -c -o root -g wheel -m 644 .indent.pro \
	    ${DESTDIR}/etc/skel/.indent.pro

.include <bsd.prog.mk>
