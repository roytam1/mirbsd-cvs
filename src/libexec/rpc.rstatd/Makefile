# $MirOS$

PROG=		rpc.rstatd
SRCS=		dkstats.c rstat_proc.c rstatd.c
MAN=		rpc.rstatd.8
CPPFLAGS+=	-I${.CURDIR}/../../usr.bin/vmstat -DNOKVM
.PATH:		${.CURDIR}/../../usr.bin/vmstat
DPADD+=		${LIBRPCSVC}
LDADD+=		-lrpcsvc

.include <bsd.prog.mk>
