# $MirOS: src/lib/libpanel/Makefile,v 1.5 2007/05/17 18:38:33 tg Exp $

LIB=		panel
DPADD+=		${LIBCURSES}
LDADD+=		-lcurses
LIBLINKS=	panelw
SHLIB_VERSION?=	6.0

NCMANSRCS+=	panel.3x

MLINKS+=	panel.3 bottom_panel.3
MLINKS+=	panel.3 del_panel.3
MLINKS+=	panel.3 hide_panel.3
MLINKS+=	panel.3 move_panel.3
MLINKS+=	panel.3 new_panel.3
MLINKS+=	panel.3 panel_above.3
MLINKS+=	panel.3 panel_below.3
MLINKS+=	panel.3 panel_hidden.3
MLINKS+=	panel.3 panel_userptr.3
MLINKS+=	panel.3 panel_window.3
MLINKS+=	panel.3 replace_panel.3
MLINKS+=	panel.3 set_panel_userptr.3
MLINKS+=	panel.3 show_panel.3
MLINKS+=	panel.3 top_panel.3
MLINKS+=	panel.3 update_panels.3

.include <bsd.own.mk>

LIBNCDIR?=	${BSDSRCDIR}/lib/libncurses
.include "${LIBNCDIR}/Makefile.inc"

CPPFLAGS+=	-I${NCSRCDIR}/ncurses -I${NCSRCDIR}/panel

.PATH: ${NCSRCDIR}/panel

SRCS+=		p_above.c
SRCS+=		p_below.c
SRCS+=		p_bottom.c
SRCS+=		p_delete.c
SRCS+=		p_hidden.c
SRCS+=		p_hide.c
SRCS+=		p_move.c
SRCS+=		p_new.c
SRCS+=		p_replace.c
SRCS+=		p_show.c
SRCS+=		p_top.c
SRCS+=		p_update.c
SRCS+=		p_user.c
SRCS+=		p_win.c
SRCS+=		panel.c

GENERATED=	ncurses_def.h
CLEANFILES+=	${GENERATED}

beforedepend: ${GENERATED}

ncurses_def.h: ${NCSRCDIR}/include/MKncurses_def.sh \
    ${NCSRCDIR}/include/ncurses_defs
	AWK=${AWK:Q} ${MKSH} ${NCSRCDIR}/include/MKncurses_def.sh \
	    ${NCSRCDIR}/include/ncurses_defs >$@

HDRS=		panel/panel.h
HDRSRC=		${NCSRCDIR}
HDRDST=		${DESTDIR}/usr/include/ncursesw

afterincludes:
	cd ${DESTDIR}/usr/include; for i in ${HDRS:T}; do \
		[[ $$(readlink $$i 2>&-) = ncursesw/$$i ]] && continue; \
		rm -f $$i; \
		ln -s ncursesw/$$i; \
	done

.include <bsd.lib.mk>

${OBJS}: ${GENERATED}
