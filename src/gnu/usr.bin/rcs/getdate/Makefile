# $MirOS: src/gnu/usr.bin/rcs/getdate/Makefile,v 1.3 2016/10/21 21:19:27 tg Exp $

PROG=		getdate
NOMAN=		yes
CPPFLAGS+=	-DTEST

NEED_RCS_LIB=	No
.include "../Makefile.inc"

CPPFLAGS+=	-I${CVSLIB}
.PATH: ${CVSLIB}

.include <bsd.prog.mk>
