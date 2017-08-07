# $MirOS: src/sbin/dump/Makefile,v 1.3 2005/03/15 19:03:51 tg Exp $
# $OpenBSD: Makefile,v 1.10 2001/04/10 20:52:10 naddy Exp $

#	dump.h			header file
#	itime.c			reads /etc/dumpdates
#	main.c			driver
#	optr.c			operator interface
#	dumprmt.c		handles remote tape via rmt(8)
#	tape.c			handles the mag tape and opening/closing
#	traverse.c		traverses the filesystem
#
#	DEBUG			use local directory to find ddate and dumpdates
#	TDEBUG			trace out the process forking

PROG=		dump
SRCS=		dumprmt.c itime.c main.c optr.c tape.c traverse.c
CPPFLAGS+=	-DRDUMP
LINKS=		${BINDIR}/dump ${BINDIR}/rdump
MAN=		dump.8
MLINKS+=	dump.8 rdump.8

.include <bsd.prog.mk>
