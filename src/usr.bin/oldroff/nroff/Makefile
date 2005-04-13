# $MirOS: src/usr.bin/oldroff/nroff/Makefile,v 1.1.7.1 2005/03/06 16:56:02 tg Exp $
# @(#)Makefile	4.7 (Berkeley) 5/11/90

PROG=	nroff
SRCS=	ni.c nii.c n1.c n2.c n3.c n4.c n5.c n6.c n7.c n8.c n9.c n10.c \
	hytab.c ntab.c suftab.c

CPPFLAGS+=	-DNROFF -DVMUNIX

.if ${OStype} != "Interix"
DPADD=	${LIBCOMPAT}
LDADD=	-lcompat
.endif

.include <bsd.prog.mk>
