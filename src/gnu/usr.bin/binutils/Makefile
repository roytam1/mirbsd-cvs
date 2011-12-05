# $MirOS: src/gnu/usr.bin/binutils/Makefile,v 1.4 2006/06/16 23:34:33 tg Exp $

  # libraries
  SUBDIR+= libiberty
  SUBDIR+= bfd
  SUBDIR+= opcodes

  # executables
  SUBDIR+= binutils
  SUBDIR+= gas
  SUBDIR+= gdb
  SUBDIR+= ld

prereq: _SUBDIRUSE

copies:
	cd bfd && cp /usr/include/bfd.h /usr/include/bfdver.h \
	    /usr/lib/libbfd.la .
	cd opcodes && cp /usr/lib/libopcodes.la .

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
