# $MirOS: ports/infrastructure/mk/mirports.miros.mk,v 1.5 2005/04/11 14:52:48 tg Exp $
#-
# MirPorts plug-in for current MirOS versions

CXX?=			c++
FETCH_CMD?=		/usr/bin/ftp -EV -m
HAS_TIMET64=		Yes
SYSTRACE_ARGS_ADD+=	-e
OSREV?=			${OSrev}

# Version dependencies
.if ${OSrev} < 8
ERRORS+=		'Configuration error. Do a "cd /usr/ports; make setup".'
.endif

.if ${OSrpl} < 40
HAS_CXX=		reason
NO_CXX=			C++ is still broken, please update
.endif
