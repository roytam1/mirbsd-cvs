# $MirOS: ports/infrastructure/mk/mirports.bsd.mk,v 1.2.2.2 2005/08/28 18:59:43 tg Exp $
#-
# This file replaces <bsd.own.mk> as EXTRA_SYS_MK_INCLUDES
# during MirPorts builds.

.ifndef _MIRPORTS_BSD_MK
_MIRPORTS_BSD_MK=1

# If we have TRUEPREFIX, this is MirPorts; if DESTDIR is not
# empty, there is no need to carry it around in PREFIX
.if defined(DESTDIR) && !empty(DESTDIR) && defined(TRUEPREFIX)
PREFIX:=		${TRUEPREFIX}
.endif

# MirMake uses BSD_PREFIX internally now
BSD_PREFIX=		${PREFIX}

# Now, system configuration.

# First, get the defaults.
.include <bsd.own.mk>

# Second, override where necessary.
DEBUGLIBS=		No
DEBUGPROGS=		No

.endif
