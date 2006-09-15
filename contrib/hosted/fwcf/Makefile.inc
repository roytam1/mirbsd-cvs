# $MirOS$

__CRAZY=		Yes

UNAME_S!=		uname -s

.if ${UNAME_S} == "OpenBSD"
CPPFLAGS+=		-D'__RCSID(x)=static const char __rcsid[] = (x)'
.endif
