# $MirOS: src/gnu/share/locations.mk,v 1.2 2005/02/11 14:34:12 tg Exp $

# for BSDSRCDIR
.include <bsd.own.mk>

# keep this in sync with reality
GNU_ROOTDIR?=		${BSDSRCDIR}/gnu

# keep this in sync with reality and <bsd.own.mk>
GNUSYSTEM_AUX_DIR=	${GNU_ROOTDIR}/share

# binutils
GNU_BINUTILS_SRC?=	${GNU_ROOTDIR}/usr.bin/binutils
#GNU_BINUTILS_SRC?=	${BSDSRCDIR}/testing/binutils
GNU_BINUTILS_AS=	${GNU_BINUTILS_SRC}/gas
GNU_BINUTILS_BFD=	${GNU_BINUTILS_SRC}/bfd
GNU_BINUTILS_BU=	${GNU_BINUTILS_SRC}/binutils
GNU_BINUTILS_GDB=	${GNU_BINUTILS_SRC}/gdb
GNU_BINUTILS_LD=	${GNU_BINUTILS_SRC}/ld
GNU_BINUTILS_OPC=	${GNU_BINUTILS_SRC}/opcodes

# gcc3-core location
GNU_COREGCC_SRC?=	${BSDSRCDIR}/gcc/gcc

# libiberty and binutils includes
GNU_LIBIBERTY_SRC?=	${GNU_BINUTILS_SRC}/libiberty
GNU_LIBIBERTY_INC?=	${GNU_BINUTILS_SRC}/include

# contrib_dir for ports/infrastructure/db et al.
GNU_AUX_CONTRIB_DIR?=	${BSDSRCDIR}/contrib
