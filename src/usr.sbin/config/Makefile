# $MirOS: src/usr.sbin/config/Makefile,v 1.5 2007/02/19 03:03:29 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/07/22 17:15:13 brad Exp $

.include <bsd.own.mk>

PROG=		config
SRCS=		files.c gram.y hash.c main.c mkheaders.c mkioconf.c \
		mkmakefile.c mkswap.c pack.c scan.l sem.c util.c \
		ukc.c misc.c ukcutil.c cmd.c exec.c
.if ${OBJECT_FMT:U} == "ELF"
CPPFLAGS+=	-DELF_SUPPORT
SRCS+=		exec_elf.c
.else
CPPFLAGS+=	-DAOUT_SUPPORT
SRCS+=		exec_aout.c
.endif

.ifdef __CRAZY
EXPERIMENTAL=	Yes
.endif

CPPFLAGS+=	-I.

LDADD=		-lkvm -lz
DPADD=		${LIBKVM} ${LIBZ}

CLEANFILES+=	gram.c scan.c y.tab.h
MAN=		config.8

beforedepend: gram.c scan.c

.include <bsd.prog.mk>
