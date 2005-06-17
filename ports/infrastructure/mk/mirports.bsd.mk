# $MirOS$
#-
# This file replaces <bsd.own.mk> as EXTRA_SYS_MK_INCLUDES
# during MirPorts builds.

.ifndef _MIRPORTS_BSD_MK
_MIRPORTS_BSD_MK=1

# First, get the defaults.
.include <bsd.own.mk>

# Second, override where necessary.
DEBUGLIBS=		No

.endif
