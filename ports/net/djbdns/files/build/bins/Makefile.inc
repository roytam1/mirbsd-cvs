# $MirOS$

.ifndef _DJBDNS_BINS_MAKEFILE_INC
_DJBDNS_BINS_MAKEFILE_INC=1

.if exists(${.CURDIR}/../lib/${__objdir})
LDADD+=		-L${.CURDIR}/../lib/${__objdir} -ldjbdns
DPADD+=		${.CURDIR}/../lib/${__objdir}/libdjbdns.a
.else
LDADD+=		-L${.CURDIR}/../lib -ldjbdns
DPADD+=		${.CURDIR}/../lib/libdjbdns.a
.endif

CPPFLAGS+=	-I${.CURDIR} -I${.CURDIR}/../include -I${srcdir}

.include "../Makefile.inc"

.endif
