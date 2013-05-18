# $MirOS: src/gnu/usr.sbin/sendmail/doc/op/Makefile,v 1.2 2005/03/13 15:11:44 tg Exp $
# @(#)Makefile	8.2 (Berkeley) 2/28/1994

DIR=	smm/08.sendmailop
SRCS=	op.me
MACROS=	-me

paper.ps: ${SRCS}
	${PIC} ${SRCS} | ${EQN} | ${ROFF} > ${.TARGET}

.include <bsd.doc.mk>
