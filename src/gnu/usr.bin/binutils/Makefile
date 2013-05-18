# $MirOS: src/gnu/usr.bin/binutils/Makefile,v 1.7 2007/06/07 00:46:24 tg Exp $

.include <bsd.own.mk>

  # libraries
# SUBDIR+= libiberty	# now pulled from src/lib/Makefile
  SUBDIR+= bfd
  SUBDIR+= opcodes

  # executables
  SUBDIR+= binutils
  SUBDIR+= gas
.if ${NOPIC:L} == "no"
  SUBDIR+= gdb
.endif
  SUBDIR+= ld

build prereq: _SUBDIRUSE

copies:
	cd bfd && cp /usr/include/bfd.h /usr/include/bfdver.h \
	    /usr/lib/libbfd.la .
	cd opcodes && cp /usr/lib/libopcodes.la .

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
