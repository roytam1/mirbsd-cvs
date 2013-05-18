# $MirOS: src/gnu/usr.sbin/sendmail/libsmdb/Makefile,v 1.3 2008/05/07 13:15:22 tg Exp $
# $OpenBSD: Makefile,v 1.3 2000/05/15 03:37:31 millert Exp $

LIB=	smdb
SRCS=	smdb.c smdb1.c smdb2.c smndbm.c
ENVDEF=	-DNOT_SENDMAIL

# This is not a library that gets installed so only build the .a version
NOPIC=	yes

.include <bsd.lib.mk>
