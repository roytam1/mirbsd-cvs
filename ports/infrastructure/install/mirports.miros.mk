# $MirOS$
#-
# MirPorts plug-in for current MirOS versions

CXX?=			c++
FETCH_CMD?=		/usr/bin/ftp -EV -m
HAS_CXX=		port
HAS_TIMET64=		Yes
SYSTRACE_ARGS_ADD+=	-e
_CXX_BR_DEPENDS=	:gcc->=3.4.0:
_CXX_LIB_DEPENDS=

# Version dependencies
.if ${OSrev} < 8
ERRORS+=		'Configuration error. Do a "cd /usr/ports; make setup".'
.endif
