# $MirOS$

.ifndef _MODSRC_GNU_USR_BIN_BINUTILS_MAKEFILE_INC
_MODSRC_GNU_USR_BIN_BINUTILS_MAKEFILE_INC=1

.include <bsd.own.mk>
.include "${GNUSYSTEM_AUX_DIR}/locations.mk"

CFARGS+=	--prefix=/usr --infodir=/usr/share/info --disable-nls \
		--mandir=/usr/share/man --disable-generated-files-in-srcdir \
		--enable-build-warnings --with-mmap --with-system-zlib \
		--enable-targets=all --enable-64-bit-bfd \
		--enable-static ${CF_PIC} --enable-install-libbfd

XARGS+=		BISON=yacc LIBIBERTY_HDRS="${GNU_LIBIBERTY_INC}"

CFLAGS+=	-Wall

.if exists(../Makefile.inc)
.  include "../Makefile.inc"
.endif

.endif
