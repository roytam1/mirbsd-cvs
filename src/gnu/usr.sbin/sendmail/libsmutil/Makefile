# $MirOS: src/gnu/usr.sbin/sendmail/libsmutil/Makefile,v 1.4 2008/05/07 13:15:22 tg Exp $
# $OpenBSD: Makefile,v 1.5 2004/11/02 21:12:15 pefo Exp $

LIB=	smutil
SRCS=	debug.c err.c lockfile.c safefile.c snprintf.c cf.c
ENVDEF=	-DNOT_SENDMAIL

# This is not a library that gets installed so only build the .a version
NOPIC=	yes

.include <bsd.lib.mk>
