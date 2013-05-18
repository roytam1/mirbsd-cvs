# $MirOS: src/gnu/usr.bin/Makefile,v 1.11 2007/06/12 21:11:22 tg Exp $

.include <bsd.own.mk>

  SUBDIR+= binutils
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= cvs anoncvs
.  if ${NOPIC:L} == "no"
  SUBDIR+= lynx
.  endif
.endif
  SUBDIR+= mkisofs
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= perl		# must be after binutils (why?)
.endif
  SUBDIR+= rcs
  SUBDIR+= texinfo	# last, builds the info 'dir' file

.include <bsd.subdir.mk>
