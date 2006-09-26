# $MirOS: contrib/hosted/fwcf/lib/Makefile,v 1.2 2006/09/23 19:47:39 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/licence for details.

LIB=		fwcf
NOPIC=		Yes
SRCS+=		compress.c
SRCS+=		cpr_get.c
SRCS+=		cpr_list.c
SRCS+=		cpr_lsth.c
SRCS+=		ft_creat.c
SRCS+=		ft_dump.c
SRCS+=		ft_pack.c
SRCS+=		ft_packm.c
SRCS+=		fts_debg.c
SRCS+=		fts_subs.c
SRCS+=		header.c
SRCS+=		unwraps.c
SRCS+=		wraps.c

CFLAGS_header.o+= -DDEBUG_ADLER

.include <bsd.lib.mk>
