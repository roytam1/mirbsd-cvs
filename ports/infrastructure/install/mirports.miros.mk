# $MirOS: ports/infrastructure/mk/mirports.miros.mk,v 1.4 2005/03/29 12:41:56 tg Exp $
#-
# MirPorts plug-in for current MirOS versions

CXX?=			c++
FETCH_CMD?=		/usr/bin/ftp -EV -m
HAS_TIMET64=		Yes
SYSTRACE_ARGS_ADD+=	-e
HAS_CXX=		reason
NO_CXX=			C++ is still broken
OSREV?=			${OSrev}

# Version dependencies
.if ${OSrev} < 8
ERRORS+=		'Configuration error. Do a "cd /usr/ports; make setup".'
.endif
