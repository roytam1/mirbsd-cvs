# $MirOS: contrib/hosted/fwcf/GNUmakefile,v 1.2 2006/09/24 00:28:32 tg Exp $
#-
# This file is part of the FreeWRT project. FreeWRT is copyrighted
# material, please see the LICENCE file in the top-level directory
# or at http://www.freewrt.org/license for details.

SRCS=		tool.c
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

# build for the target
CFLAGS+=	-DSMALL

# missing in uClibc
SRCS+=		fts.c
CFLAGS+=	-I.

all: fwcf.helper.out

fwcf.helper.out: ${OBJS}
	${CC} -o $@ ${OBJS} ${LDFLAGS} -lz
