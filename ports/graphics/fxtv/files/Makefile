# $MirOS$

.include <bsd.own.mk>

BINDIR=		${PREFIX}/bin
MANDIR=		${PREFIX}/man/cat
FXTV_LIBDIR=	${LOCALBASE}/share/fxtv
#.PATH=		videolib

PROG=		fxtv
SRCS=		actions.c annot.c appear_dlg.c \
		audiocnvt.c audsav_dlg.c batch_mode.c glob.c haup_remote.c \
		imgsav.c imgsav_dlg.c pixelview_remote.c rawvideo.c remote.c \
		remotetrans.c station.c tv.c tvaudio.c tvcapture.c tvmenu.c \
		tvscreen.c tvutil.c vidsav_dlg.c xutil.c
OBJS+=		videolib.o
MAN=		fxtv.1

CPPFLAGS+=	-DVERS_STR=\"1.03\" -DNDEBUG -DHAVE_XFREE86 \
		-DX11BASE=\"${X11BASE}\" -DFXTV_LIBDIR=\"${FXTV_LIBDIR}/%T/%N\" \
		-I. -Ivideolib -I${X11BASE}/include -I${LOCALBASE}/include
LDFLAGS+=	-L${LOCALBASE}/lib -L${X11BASE}/lib -ltiff -ljpeg -lz -lXaw3d \
		-lXmu -lXt -lXpm -lSM -lICE -lXext -lX11 -lm -lXxf86dga \
		-lXxf86vm -lossaudio 

tv.o: tv.c app_rsrc.h

videolib.o: videolib/videolib.c

.if defined(DESTDIR) && !empty(DESTDIR) && defined(TRUEPREFIX)
PREFIX:=        ${TRUEPREFIX}
.endif

.include <bsd.prog.mk>
