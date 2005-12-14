# $MirOS: ports/net/djbdns/files/build/bins/Makefile.inc,v 1.1.201.1 2005/05/14 23:21:07 tg Exp $

.ifndef _DJBDNS_BINS_MAKEFILE_INC
_DJBDNS_BINS_MAKEFILE_INC=1

.if exists(${.CURDIR}/../libt6/${__objdir})
LDADD+=		-L${.CURDIR}/../libt6/${__objdir} -ldjbdnst6
DPADD+=		${.CURDIR}/../libt6/${__objdir}/libdjbdnst6.a
.else
LDADD+=		-L${.CURDIR}/../libt6 -ldjbdnst6
DPADD+=		${.CURDIR}/../libt6/libdjbdnst6.a
.endif

.include "../Makefile.inc"

CPPFLAGS+=	-DDJB_V6ONLY
NOMAN=		Yes

.endif
