# $MirOS: ports/infrastructure/mk/mirports.miros.mk,v 1.1.7.1 2005/03/18 15:47:19 tg Exp $
#-
# MirPorts plug-in for current MirOS versions

CXX?=			c++
FETCH_CMD?=		/usr/bin/ftp -EV -m
HAS_CXX=		port
HAS_TIMET64=		Yes
SYSTRACE_ARGS_ADD+=	-e
_CXX_BR_DEPENDS=
_CXX_LIB_DEPENDS=

# Version dependencies
.if ${OSrev} < 8
ERRORS+=		'Configuration error. Do a "cd /usr/ports; make setup".'
.endif
