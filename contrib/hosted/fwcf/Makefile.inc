# $MirOS: contrib/hosted/fwcf/Makefile.inc,v 1.1 2006/09/15 21:11:23 tg Exp $

__CRAZY=		Yes
MKC_DEBG=		cpp

UNAME_S!=		uname -s

.if ${UNAME_S} == "OpenBSD"
CPPFLAGS+=		-D'__RCSID(x)=static const char __rcsid[] = (x)'
.endif
