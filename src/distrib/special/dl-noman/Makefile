# $MirOS: src/distrib/special/dl-noman/Makefile,v 1.1 2006/09/29 22:25:36 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/sbin/disklabel
NOMAN=		yes

.if ${MACHINE_ARCH} == "sparc"
CPPFLAGS+=	-DSMALL
.endif

.include "${SRC_PATH}/Makefile"
