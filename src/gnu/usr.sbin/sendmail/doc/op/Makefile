# $MirOS: src/gnu/usr.sbin/sendmail/doc/op/Makefile,v 1.3 2008/05/07 13:15:17 tg Exp $
# @(#)Makefile	8.2 (Berkeley) 2/28/1994

DIR=	smm/08.sendmailop
SRCS=	op.me
MACROS=	-me
EXTRA=	README

paper.ps: ${SRCS}
	${PIC} ${SRCS} | ${EQN} | ${ROFF} > ${.TARGET}

.include <bsd.doc.mk>
