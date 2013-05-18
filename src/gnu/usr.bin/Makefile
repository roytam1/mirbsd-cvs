# $MirOS: src/gnu/usr.bin/Makefile,v 1.12 2007/06/12 21:37:01 tg Exp $

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
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= texinfo	# last, builds the info 'dir' file
.endif

.include <bsd.subdir.mk>
