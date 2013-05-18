# $MirOS: src/distrib/special/Makefile,v 1.10 2006/09/22 15:40:02 tg Exp $
#-
# Tools which must be compiled differently for
# the small or floppy ramdiscs because of missing
# libraries or simply to be smaller

.if ${MACHINE} == "i386"
  SUBDIR+=	chat
  SUBDIR+=	dl-noman	# without integrated manpage
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
