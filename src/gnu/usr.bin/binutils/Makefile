# $MirOS: src/gnu/usr.bin/binutils/Makefile,v 1.3 2005/06/14 00:12:51 tg Exp $

  # libraries
  SUBDIR+= libiberty
  SUBDIR+= bfd
  SUBDIR+= opcodes

  # executables
  SUBDIR+= binutils
  SUBDIR+= gas
.if ${MACHINE} != "sparc"
  SUBDIR+= gdb
.endif
  SUBDIR+= ld

prereq: _SUBDIRUSE

copies:
	cd bfd && cp /usr/include/bfd.h /usr/include/bfdver.h \
	    /usr/lib/libbfd.la .
	cd opcodes && cp /usr/lib/libopcodes.la .

.include <bsd.obj.mk>
.include <bsd.subdir.mk>
