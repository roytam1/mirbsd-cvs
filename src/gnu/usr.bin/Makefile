# $MirOS: src/gnu/usr.bin/Makefile,v 1.8 2006/06/16 23:48:34 tg Exp $

.include <bsd.own.mk>

  SUBDIR+= binutils
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= cvs
  SUBDIR+= anoncvs	# must be after CVS
.  if ${NOPIC:L} == "no"
  SUBDIR+= lynx
.  endif
  SUBDIR+= mkisofs
  SUBDIR+= perl		# must be after binutils (why?)
  SUBDIR+= rcs
  SUBDIR+= texinfo	# last, builds the info 'dir' file
.endif

.include <bsd.subdir.mk>
