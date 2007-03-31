# $MirOS: ports/infrastructure/install/mirports.sys.mk,v 1.3 2005/12/20 19:17:39 tg Exp $

.ifndef MIRPORTS_SYS_MK

.ifdef BSD_OWN_MK
.  error Never .include <bsd.own.mk> in MirPorts, always .include <mirports.sys.mk>
.endif

# Note these two are not necessarily coupled to each other
PORTSDIR?=	@
LOCALBASE?=	@

.if exists(${LOCALBASE}/db/SetEnv.make)
.  include "${LOCALBASE}/db/SetEnv.make"
.endif

.include <bsd.own.mk>

.if exists(${PORTSDIR}/infrastructure/mk/mirports.sys.mk)
.  include "${PORTSDIR}/infrastructure/mk/mirports.sys.mk"
.endif

.endif
