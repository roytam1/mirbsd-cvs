# $MirOS: ports/infrastructure/mk/mirports.miros.mk,v 1.2 2005/03/27 18:37:20 tg Exp $
#-
# MirPorts plug-in for current MirOS versions

CXX?=			c++
FETCH_CMD?=		/usr/bin/ftp -EV -m
HAS_CXX=		port
HAS_TIMET64=		Yes
SYSTRACE_ARGS_ADD+=	-e

# Version dependencies
.if ${OSrev} < 8
ERRORS+=		'Configuration error. Do a "cd /usr/ports; make setup".'
.endif
