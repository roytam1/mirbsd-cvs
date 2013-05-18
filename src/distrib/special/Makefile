# $MirOS: src/distrib/special/Makefile,v 1.7 2006/05/26 18:49:49 tg Exp $
#-
# Tools which must be compiled differently for
# the small or floppy ramdiscs because of missing
# libraries or simply to be smaller

.if ${MACHINE} == "i386"
  SUBDIR+=	chat
.endif
  SUBDIR+=	dmesg
  SUBDIR+=	ftp
  SUBDIR+=	more
.if ${MACHINE} == "i386"
  SUBDIR+=	pppd
.endif
  SUBDIR+=	vnconfig

.include <bsd.subdir.mk>
