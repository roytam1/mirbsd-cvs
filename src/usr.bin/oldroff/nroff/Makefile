# $MirOS$
# @(#)Makefile	4.7 (Berkeley) 5/11/90

PROG=	nroff
SRCS=	ni.c nii.c n1.c n2.c n3.c n4.c n5.c n6.c n7.c n8.c n9.c n10.c \
	hytab.c ntab.c suftab.c

CPPFLAGS+=	-DNROFF -DVMUNIX

DPADD=	${LIBCOMPAT}
LDADD=	-lcompat

.include <bsd.prog.mk>
