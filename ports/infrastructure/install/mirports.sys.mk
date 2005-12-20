# $MirOS: ports/infrastructure/install/mirports.sys.mk,v 1.2 2005/09/12 22:53:17 tg Exp $

.ifndef MIRPORTS_SYS_MK

# Note these two are not necessarily coupled to each other
PORTSDIR?=	@
LOCALBASE?=	@

.if exists(${LOCALBASE}/db/SetEnv.make)
.  include "${LOCALBASE}/db/SetEnv.make"
.endif

.ifndef BSD_OWN_MK
.  include <bsd.own.mk>
.endif

.if exists(${PORTSDIR}/infrastructure/mk/mirports.sys.mk)
.  include "${PORTSDIR}/infrastructure/mk/mirports.sys.mk"
.endif

.endif
