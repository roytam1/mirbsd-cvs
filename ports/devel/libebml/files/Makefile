# $MirOS$

LIB=		ebml
SRCS=		Debug.cpp EbmlBinary.cpp EbmlContexts.cpp EbmlCrc32.cpp \
		EbmlDate.cpp EbmlDummy.cpp EbmlElement.cpp EbmlFloat.cpp \
		EbmlHead.cpp EbmlMaster.cpp EbmlSInteger.cpp EbmlStream.cpp \
		EbmlString.cpp EbmlSubHead.cpp EbmlUInteger.cpp \
		EbmlUnicodeString.cpp EbmlVersion.cpp EbmlVoid.cpp \
		IOCallback.cpp MemIOCallback.cpp StdIOCallback.cpp
INCS=		c/libebml_t.h Debug.h EbmlBinary.h EbmlConfig.h \
		EbmlContexts.h EbmlCrc32.h EbmlDate.h EbmlDummy.h \
		EbmlElement.h EbmlEndian.h EbmlFloat.h EbmlHead.h \
		EbmlId.h EbmlMaster.h EbmlSInteger.h EbmlStream.h \
		EbmlString.h EbmlSubHead.h EbmlTypes.h EbmlUInteger.h \
		EbmlUnicodeString.h EbmlVersion.h EbmlVoid.h \
		IOCallback.h MemIOCallback.h StdIOCallback.h

SRCDIR=		src
INCDIR=		${LIB}
LIBDIR=		${PREFIX}/lib
CXXFLAGS+=	-Wall -Wno-unknown-pragmas -ansi -fno-gnu-keywords -Wshadow

.if defined(DESTDIR) && !empty(DESTDIR) && defined(TRUEPREFIX)
PREFIX:=	${TRUEPREFIX}
.endif
INSTALL_DATA_DIR?=${BSD_INSTALL_DATA_DIR}
INSTALL_DATA?=${BSD_INSTALL_DATA}

NOMAN=		yes
NOPIC=		yes

beforeinstall:
	${INSTALL_DATA_DIR} ${DESTDIR}${PREFIX}/include/${INCDIR}/c
.for i in ${INCS}
	${INSTALL_DATA} ${INCDIR}/$i ${DESTDIR}${PREFIX}/include/${INCDIR}/$i
.endfor

.include <bsd.lib.mk>

.PATH:		${SRCDIR}
.SUFFIXES:	.cpp

.cpp.cc:
	@cp ${.IMPSRC} ${.TARGET}
