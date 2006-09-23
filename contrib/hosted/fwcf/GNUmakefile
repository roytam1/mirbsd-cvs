# $MirOS: contrib/hosted/fwcf/fwcf.helper/Makefile,v 1.1 2006/09/23 23:04:15 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

SRCS=		fwcf.helper.c
SRCS+=		c_zlib.c
SRCS+=		sys_linux.c
SRCS+=		compress.c
SRCS+=		cpr_get.c
SRCS+=		cpr_list.c
SRCS+=		cpr_lsth.c
SRCS+=		ft_creat.c
SRCS+=		ft_pack.c
SRCS+=		ft_packm.c
SRCS+=		fts_subs.c
SRCS+=		header.c
SRCS+=		unwraps.c
SRCS+=		wraps.c

OBJS=		${SRCS:.c=.o}

all: fwcf.helper.out

fwcf.helper.out: ${OBJS}
	${CC} -o $@ ${OBJS} -lz
