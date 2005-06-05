# $MirOS: src/gnu/usr.bin/binutils/Makefile.inc,v 1.1.7.1 2005/03/06 16:58:49 tg Exp $

.ifndef _MODSRC_GNU_USR_BIN_BINUTILS_MAKEFILE_INC
_MODSRC_GNU_USR_BIN_BINUTILS_MAKEFILE_INC=1

.include <bsd.own.mk>
.include "${GNUSYSTEM_AUX_DIR}/locations.mk"

CFARGS+=	--prefix=/usr --infodir=/usr/share/info --disable-nls \
		--mandir=/usr/share/man --disable-generated-files-in-srcdir \
		--enable-build-warnings --with-mmap --with-system-zlib \
		--enable-targets=all --enable-64-bit-bfd \
		--enable-static --disable-shared --enable-install-libbfd

XARGS+=		BISON=yacc LIBIBERTY_HDRS="${GNU_LIBIBERTY_INC}"

CFLAGS+=	-Wall

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
