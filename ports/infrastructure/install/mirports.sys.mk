# $MirOS$
#
# Please install these using the ports/setup.sh script provided.

.ifndef MIRPORTS_SYS_MK

.  ifndef BSD_OWN_MK
.    include <bsd.own.mk>
.  endif

PORTSDIR?=	/usr/ports

# If the user wants to use the OpenBSD ports tree and the
# MirPorts framework in parallel, he shall do so.
.  if exists(${PORTSDIR}/infrastructure/mk/mirports.sys.mk)
.    include "${PORTSDIR}/infrastructure/mk/mirports.sys.mk"
.  endif

.endif
