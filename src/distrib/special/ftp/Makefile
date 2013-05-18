# $MirOS: src/distrib/ramtools/ppp/Makefile,v 1.1 2006/05/15 19:20:17 tg Exp $

# Uncomment the following to provide defaults for gate-ftp operation
#CPPFLAGS+=-DGATE_SERVER=\"ftp-gw.host\" # -DGATE_PORT=21

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/usr.bin/ftp

SMALL=		defined
#NO_INET6=	defined

.include "${SRC_PATH}/Makefile"
