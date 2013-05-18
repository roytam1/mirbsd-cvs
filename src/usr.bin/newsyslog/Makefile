# $MirOS$
# $OpenBSD: Makefile,v 1.5 2001/08/21 17:25:05 deraadt Exp $

PROG=	newsyslog

CPPFLAGS+= -DCONF=\"/etc/newsyslog.conf\"
CPPFLAGS+= -DPIDFILE=\"/var/run/syslog.pid\"
CPPFLAGS+= -DCOMPRESS=\"/usr/bin/gzip\"
CPPFLAGS+= -DCOMPRESS_POSTFIX=\".gz\"
CPPFLAGS+= -DSTATS_DIR=\"/var/run\"
CPPFLAGS+= -DSENDMAIL=\"/usr/sbin/sendmail\"
CPPFLAGS+= -DQUAD_OFF_T

MAN=	newsyslog.8
MLINKS=	newsyslog.8 newsyslog.conf.5

.include <bsd.prog.mk>
