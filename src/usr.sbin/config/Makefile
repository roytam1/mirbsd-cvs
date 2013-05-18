# $MirOS: src/usr.sbin/config/Makefile,v 1.7 2007/04/28 00:12:51 tg Exp $
# $OpenBSD: Makefile,v 1.13 2003/07/22 17:15:13 brad Exp $

.include <bsd.own.mk>

PROG=		config
MAN=		config.8
SRCS=		files.c gram.y hash.c main.c mkheaders.c mkioconf.c \
		mkmakefile.c mkswap.c pack.c scan.l sem.c util.c \
		ukc.c ukcmain.c misc.c ukcutil.c cmd.c exec.c
.if ${OBJECT_FMT:U} == "ELF"
CPPFLAGS+=	-DELF_SUPPORT
SRCS+=		exec_elf.c
.else
CPPFLAGS+=	-DAOUT_SUPPORT
SRCS+=		exec_aout.c
.endif

.ifdef __CRAZY
CFLAGS_main.o=		-Wno-error	#XXX ht_insert "data" arg const
CFLAGS_sem.o=		-Wno-error	#XXX ht_insert "data" arg const
CFLAGS_ukcmain.o=	-Wno-error	#XXX struct nlist initialisation
.endif

CPPFLAGS+=	-I.

LDADD=		-lkvm -lz
DPADD=		${LIBKVM} ${LIBZ}

.include <bsd.prog.mk>
