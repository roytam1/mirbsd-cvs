# $MirOS$

LIB=		matroska
SRCS=		FileKax.cpp KaxAttached.cpp KaxAttachments.cpp KaxBlock.cpp \
		KaxBlockData.cpp KaxChapters.cpp KaxCluster.cpp \
		KaxClusterData.cpp KaxContentEncoding.cpp KaxContexts.cpp \
		KaxCues.cpp KaxCuesData.cpp KaxInfo.cpp KaxInfoData.cpp \
		KaxSeekHead.cpp KaxSegment.cpp KaxTag.cpp KaxTagMulti.cpp \
		KaxTags.cpp KaxTrackAudio.cpp KaxTrackEntryData.cpp \
		KaxTrackVideo.cpp KaxTracks.cpp KaxVersion.cpp
INCS=		c/libmatroska.h c/libmatroska_t.h FileKax.h KaxAttached.h \
		KaxAttachments.h KaxBlock.h KaxBlockData.h KaxChapters.h \
		KaxCluster.h KaxClusterData.h KaxConfig.h \
		KaxContentEncoding.h KaxContexts.h KaxCues.h KaxCuesData.h \
		KaxInfo.h KaxInfoData.h KaxSeekHead.h KaxSegment.h KaxTag.h \
		KaxTagMulti.h KaxTags.h KaxTrackAudio.h KaxTrackEntryData.h \
		KaxTrackVideo.h KaxTracks.h KaxTypes.h KaxVersion.h

SRCDIR=		src
INCDIR=		${LIB}
LIBDIR=		${PREFIX}/lib
CXXFLAGS+=	-Wall -Wno-unknown-pragmas -ansi -fno-gnu-keywords \
		-D_GNU_SOURCE -Wshadow
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
