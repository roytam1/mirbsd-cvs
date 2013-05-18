# $MirOS: src/lib/librpcsvc/Makefile,v 1.2 2005/03/06 20:29:22 tg Exp $
# $OpenBSD: Makefile,v 1.7 2003/06/23 18:50:53 mickey Exp $

RPCSRCS=	bootparam_prot.x klm_prot.x mount.x nfs_prot.x \
		nlm_prot.x rex.x rnusers.x rusers.x rquota.x rstat.x rwall.x \
		sm_inter.x spray.x
SRCS=		${RPCSRCS:R:S/$/.c/g}
CLEANFILES+=	${SRCS} ${RPCSRCS:R:S/$/.h/g}

LIB=		rpcsvc
NOMAN=		yes
NOPIC=		yes

all:		${RPCSRCS:R:S/$/.h/g}
beforedepend:	${RPCSRCS:R:S/$/.h/g}
prereq:		${RPCSRCS:R:S/$/.h/g}

HDRDST=		${DESTDIR}/usr/include/rpcsvc
HDRS=		${RPCSRCS} ${RPCSRCS:R:S/$/.h/g:S!^!${.OBJDIR}/!}

# new suffixes have to go afterwards, because bsd.lib.mk clears them
.include <bsd.lib.mk>
.SUFFIXES: .x .c .h

.x.c:
	rpcgen -C -c ${.IMPSRC} -o ${.TARGET}

.x.h:
	rpcgen -C -h ${.IMPSRC} -o ${.TARGET}
