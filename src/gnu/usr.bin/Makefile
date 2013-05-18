# $MirOS: src/gnu/usr.bin/Makefile,v 1.14 2007/06/12 21:44:10 tg Exp $

.include <bsd.own.mk>

  SUBDIR+= binutils
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= cvs anoncvs
.  if ${NOPIC:L} == "no"
  SUBDIR+= lynx
.  endif
  SUBDIR+= perl		# must be after binutils (why?)
  SUBDIR+= rcs
  SUBDIR+= texinfo	# last, builds the info 'dir' file
.endif

.include <bsd.subdir.mk>
