# $MirOS: src/gnu/usr.sbin/sendmail/libsmutil/Makefile,v 1.5 2010/12/19 17:18:14 tg Exp $
# $OpenBSD: Makefile,v 1.6 2010/02/03 20:49:00 miod Exp $

LIB=	smutil
SRCS=	debug.c err.c lockfile.c safefile.c snprintf.c cf.c
ENVDEF=	-DNOT_SENDMAIL

# This is not a library that gets installed so only build the .a version
NOPIC=	yes

.include <bsd.lib.mk>
