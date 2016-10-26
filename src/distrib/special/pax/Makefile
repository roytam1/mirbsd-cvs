# $MirOS: src/distrib/special/pax/Makefile,v 1.1 2016/03/12 12:53:29 tg Exp $

.include <bsd.own.mk>

SRC_PATH=	${BSDSRCDIR}/bin/pax

PROG=		pax
SRCS=		ar_io.c ar_subs.c buf_subs.c cache.c cpio.c file_subs.c \
		ftree.c gen_subs.c getoldopt.c options.c pat_rep.c pax.c \
		sel_subs.c tables.c tar.c tty_subs.c
CPPFLAGS+=	-DPAX_SAFE_PATH=\"/bin:/usr/bin\"
CPPFLAGS+=	-DHAVE_STRLCPY
CPPFLAGS+=	-DHAVE_STRMODE
CPPFLAGS+=	-DHAVE_VIS
CPPFLAGS+=	-DSMALL

.include <bsd.prog.mk>
