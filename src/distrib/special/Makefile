# $MirOS: src/distrib/special/Makefile,v 1.13 2007/01/26 18:50:26 tg Exp $
#-
# Tools which must be compiled differently for
# the small or floppy ramdiscs because of missing
# libraries or simply to be smaller

.if ${MACHINE} == "i386"
# SUBDIR+=	chat		# i386 floppy
  SUBDIR+=	dl-noman	# i386 floppy, without integrated manpage
.endif
  SUBDIR+=	dmesg		# i386 floppy, sparc floppy + miniroot
.if ${MACHINE} == "i386"
  SUBDIR+=	fdisk		# i386 floppy, without integrated manpage
.endif
  SUBDIR+=	ftp		# i386 floppy, sparc floppy + miniroot
  SUBDIR+=	init		# i386 floppy + bsd.rd, sparc floppy + mr
  SUBDIR+=	less		# i386 bsd.rd, sparc miniroot
  SUBDIR+=	mksh		# i386 floppy, sparc floppy + miniroot
  SUBDIR+=	more		# i386 floppy, sparc floppy
.if ${MACHINE} == "i386"
  SUBDIR+=	ppp		# i386 bsd.rd
# SUBDIR+=	pppd		# i386 floppy
  SUBDIR+=	sshd		# i386 bsd.rd
.endif
  SUBDIR+=	vnconfig	# i386 floppy, sparc floppy + miniroot

.include <bsd.subdir.mk>
