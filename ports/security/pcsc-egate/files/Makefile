# $MirOS$

SRCS=	egate.c ifdhandler.c
LIB=	ifd_egate

LDADD+=	${LDFLAGS} -lusb

SHLIB_VERSION=0.0
SHLIB_MAJOR=0
SHLIB_MINOR=0

TGTDIR=	${PREFIX}/libexec/pcsc/drivers/ifd-egate.bundle/Contents

myinstall:
	${BSD_INSTALL_DATA_DIR} ${TGTDIR}/BSD
	${BSD_INSTALL_SCRIPT} lib${LIB}.so.0.0 ${TGTDIR}/BSD/lib${LIB}.so
	${BSD_INSTALL_DATA} Info.plist ${TGTDIR}/

.include <bsd.lib.mk>
