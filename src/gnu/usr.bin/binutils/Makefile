# $MirOS: src/gnu/usr.bin/binutils/Makefile,v 1.6 2006/07/03 16:30:32 tg Exp $

  # libraries
# SUBDIR+= libiberty	# now pulled from src/lib/Makefile
  SUBDIR+= bfd
  SUBDIR+= opcodes

  # executables
  SUBDIR+= binutils
  SUBDIR+= gas
  SUBDIR+= gdb
  SUBDIR+= ld

build prereq: _SUBDIRUSE

copies:
	cd bfd && cp /usr/include/bfd.h /usr/include/bfdver.h \
	    /usr/lib/libbfd.la .
	cd opcodes && cp /usr/lib/libopcodes.la .

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
