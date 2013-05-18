# $MirOS: src/gnu/usr.bin/Makefile,v 1.6 2006/06/16 23:35:36 tg Exp $

.include <bsd.own.mk>

  SUBDIR+= binutils
  SUBDIR+= cvs
  SUBDIR+= anoncvs	# must be after CVS
  SUBDIR+= lynx
  SUBDIR+= mkisofs
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= perl		# must be after binutils (why?)
.endif
  SUBDIR+= rcs
  SUBDIR+= texinfo	# last, builds the info 'dir' file

.include <bsd.subdir.mk>
