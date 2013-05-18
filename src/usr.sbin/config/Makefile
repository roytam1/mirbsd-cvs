# $MirOS: src/usr.sbin/config/Makefile,v 1.6 2007/02/19 03:24:54 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/07/22 17:15:13 brad Exp $

.include <bsd.own.mk>

PROG=		config
MAN=		config.8
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

.include <bsd.prog.mk>
