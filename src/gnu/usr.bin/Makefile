# $MirOS: src/gnu/usr.bin/Makefile,v 1.13 2007/06/12 21:43:33 tg Exp $

.include <bsd.own.mk>

  SUBDIR+= binutils
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= cvs anoncvs
.  if ${NOPIC:L} == "no"
  SUBDIR+= lynx
.  endif
  SUBDIR+= mkisofs
  SUBDIR+= perl		# must be after binutils (why?)
  SUBDIR+= rcs
  SUBDIR+= texinfo	# last, builds the info 'dir' file
.endif

.include <bsd.subdir.mk>
