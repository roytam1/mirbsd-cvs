# $MirOS$
# $OpenBSD: Makefile,v 1.11 2003/12/18 02:27:13 millert Exp $
# $NetBSD: Makefile,v 1.2 1997/01/22 01:36:30 cgd Exp $

S=		${.CURDIR}/../../../..
ZDST=		${.OBJDIR}
SADIR=		${.CURDIR}/..
CPPFLAGS=	${SACFLAGS} -I${S}/lib/libsa ${DEBUGFLAGS} -Dzmemcpy=memmove

.PATH:		${S}/lib/libz
.include "${S}/lib/libz/Makefile"
