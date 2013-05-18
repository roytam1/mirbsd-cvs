# $MirOS: src/distrib/special/Makefile,v 1.8 2006/08/17 19:58:06 tg Exp $
#-
# Tools which must be compiled differently for
# the small or floppy ramdiscs because of missing
# libraries or simply to be smaller

.if ${MACHINE} == "i386"
  SUBDIR+=	chat
.endif
  SUBDIR+=	dmesg
  SUBDIR+=	ftp
  SUBDIR+=	init
.if ${MACHINE} == "i386"
  SUBDIR+=	less
.endif
  SUBDIR+=	more
.if ${MACHINE} == "i386"
  SUBDIR+=	ppp
  SUBDIR+=	pppd
  SUBDIR+=	sshd
.endif
  SUBDIR+=	vnconfig

.include <bsd.subdir.mk>
