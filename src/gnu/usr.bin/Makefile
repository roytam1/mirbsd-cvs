# $MirOS: src/gnu/usr.bin/Makefile,v 1.4 2005/03/27 22:52:43 tg Exp $

  SUBDIR+= binutils
  SUBDIR+= cvs
  SUBDIR+= anoncvs	# must be after CVS
  SUBDIR+= lynx
  SUBDIR+= mkisofs
.if !defined(CROSS_MODE) || (${CROSS_MODE:L} != "yes")
  SUBDIR+= perl		# must be after binutils (why?)
.endif
  SUBDIR+= rcs
  SUBDIR+= texinfo	# last, builds the info 'dir' file

.include <bsd.subdir.mk>
