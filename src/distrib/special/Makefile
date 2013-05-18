# $MirOS: src/distrib/special/Makefile,v 1.9 2006/08/17 20:13:28 tg Exp $
#-
# Tools which must be compiled differently for
# the small or floppy ramdiscs because of missing
# libraries or simply to be smaller

.if ${MACHINE} == "i386"
  SUBDIR+=	chat
  SUBDIR+=	disklabel	# without integrated manpage
.endif
  SUBDIR+=	dmesg
.if ${MACHINE} == "i386"
  SUBDIR+=	fdisk		# without integrated manpage
.endif
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
