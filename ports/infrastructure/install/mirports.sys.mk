# $MirOS: ports/infrastructure/install/mirports.sys.mk,v 1.1.7.1.2.1 2005/08/21 10:38:00 tg Exp $
#
# To install use the provided ports/infrastructure/install/Setup.sh script.

.ifndef MIRPORTS_SYS_MK

.ifndef BSD_OWN_MK
.  include <bsd.own.mk>
.endif

# Note these two are not necessarily coupled to each other
# Also don't change the defaults; this is being done by Setup.sh
PORTSDIR?=	/usr/ports	# Location of MirPorts Framework source
LOCALBASE?=	/usr/mpkg	# Location of MirPorts Packages and DB

.if exists(${LOCALBASE}/db/SetEnv.make)
.  include "${LOCALBASE}/db/SetEnv.make"
.endif

.if exists(${PORTSDIR}/infrastructure/mk/mirports.sys.mk)
.  include "${PORTSDIR}/infrastructure/mk/mirports.sys.mk"
.endif

.endif
