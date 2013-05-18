# $MirOS: src/gnu/usr.bin/Makefile,v 1.10 2007/06/12 18:44:28 tg Exp $

.include <bsd.own.mk>

  SUBDIR+= binutils
.if ${CROSS_MODE:L} != "yes"
  SUBDIR+= cvs anoncvs
.endif
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
