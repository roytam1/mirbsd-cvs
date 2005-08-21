# $MirOS: ports/infrastructure/install/mirports.sys.mk,v 1.1.7.1 2005/03/18 15:47:16 tg Exp $
#
# To install use the provided ports/infrastructure/install/Setup.sh script.

.ifndef MIRPORTS_SYS_MK

.ifndef BSD_OWN_MK
.  include <bsd.own.mk>
.endif

PORTSDIR?=	/usr/ports

# In case we are being used for "the other ports tree"...
.if exists(${PORTSDIR}/infrastructure/mk/mirports.sys.mk)
.  include "${PORTSDIR}/infrastructure/mk/mirports.sys.mk"
.endif

.endif
