# $MirOS: src/gnu/usr.bin/Makefile,v 1.9 2007/06/09 17:29:31 tg Exp $

.include <bsd.own.mk>

  SUBDIR+= binutils
  SUBDIR+= cvs
  SUBDIR+= anoncvs	# must be after CVS
.if ${NOPIC:L} == "no"
  SUBDIR+= lynx
.endif
  SUBDIR+= mkisofs
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= perl		# must be after binutils (why?)
.endif
  SUBDIR+= rcs
  SUBDIR+= texinfo	# last, builds the info 'dir' file

.include <bsd.subdir.mk>
