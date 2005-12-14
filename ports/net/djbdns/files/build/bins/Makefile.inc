# $MirOS: ports/net/djbdns/files/build/bins/Makefile.inc,v 1.1.201.1 2005/05/14 23:21:07 tg Exp $

.ifndef _DJBDNS_BINS_MAKEFILE_INC
_DJBDNS_BINS_MAKEFILE_INC=1

.if exists(${.CURDIR}/../lib/${__objdir})
LDADD+=		-L${.CURDIR}/../lib/${__objdir} -ldjbdns
DPADD+=		${.CURDIR}/../lib/${__objdir}/libdjbdns.a
.else
LDADD+=		-L${.CURDIR}/../lib -ldjbdns
DPADD+=		${.CURDIR}/../lib/libdjbdns.a
.endif

.include "../Makefile.inc"

.endif
