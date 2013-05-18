# $MirOS: src/lib/libmenu/Makefile,v 1.5 2007/05/17 18:38:32 tg Exp $

LIB=		menu
DPADD+=		${LIBCURSES}
LDADD+=		-lcurses
LIBLINKS=	menuw
SHLIB_VERSION?=	6.0

NCMANSRCS+=	menu.3x
NCMANSRCS+=	menu_attributes.3x
NCMANSRCS+=	menu_cursor.3x
NCMANSRCS+=	menu_driver.3x
NCMANSRCS+=	menu_format.3x
NCMANSRCS+=	menu_hook.3x
NCMANSRCS+=	menu_items.3x
NCMANSRCS+=	menu_mark.3x
NCMANSRCS+=	menu_new.3x
NCMANSRCS+=	menu_opts.3x
NCMANSRCS+=	menu_pattern.3x
NCMANSRCS+=	menu_post.3x
NCMANSRCS+=	menu_requestname.3x
NCMANSRCS+=	menu_spacing.3x
NCMANSRCS+=	menu_userptr.3x
NCMANSRCS+=	menu_win.3x
NCMANSRCS+=	mitem_current.3x
NCMANSRCS+=	mitem_name.3x
NCMANSRCS+=	mitem_new.3x
NCMANSRCS+=	mitem_opts.3x
NCMANSRCS+=	mitem_userptr.3x
NCMANSRCS+=	mitem_value.3x
NCMANSRCS+=	mitem_visible.3x

MLINKS+=	menu_attributes.3 menu_back.3
MLINKS+=	menu_attributes.3 menu_fore.3
MLINKS+=	menu_attributes.3 menu_grey.3
MLINKS+=	menu_attributes.3 menu_pad.3
MLINKS+=	menu_attributes.3 set_menu_back.3
MLINKS+=	menu_attributes.3 set_menu_fore.3
MLINKS+=	menu_attributes.3 set_menu_grey.3
MLINKS+=	menu_attributes.3 set_menu_pad.3
MLINKS+=	menu_cursor.3 pos_menu_cursor.3
MLINKS+=	menu_format.3 set_menu_format.3
MLINKS+=	menu_hook.3 item_init.3
MLINKS+=	menu_hook.3 item_term.3
MLINKS+=	menu_hook.3 menu_init.3
MLINKS+=	menu_hook.3 menu_term.3
MLINKS+=	menu_hook.3 set_item_init.3
MLINKS+=	menu_hook.3 set_item_term.3
MLINKS+=	menu_hook.3 set_menu_init.3
MLINKS+=	menu_hook.3 set_menu_term.3
MLINKS+=	menu_items.3 item_count.3
MLINKS+=	menu_items.3 set_menu_items.3
MLINKS+=	menu_mark.3 set_menu_mark.3
MLINKS+=	menu_new.3 free_menu.3
MLINKS+=	menu_new.3 new_menu.3
MLINKS+=	menu_opts.3 menu_opts_off.3
MLINKS+=	menu_opts.3 menu_opts_on.3
MLINKS+=	menu_opts.3 set_menu_opts.3
MLINKS+=	menu_pattern.3 set_menu_pattern.3
MLINKS+=	menu_post.3 post_menu.3
MLINKS+=	menu_post.3 unpost_menu.3
MLINKS+=	menu_requestname.3 menu_request_by_name.3
MLINKS+=	menu_requestname.3 menu_request_name.3
MLINKS+=	menu_spacing.3 set_menu_spacing.3
MLINKS+=	menu_userptr.3 set_menu_userptr.3
MLINKS+=	menu_win.3 menu_sub.3
MLINKS+=	menu_win.3 scale_menu.3
MLINKS+=	menu_win.3 set_menu_sub.3
MLINKS+=	menu_win.3 set_menu_win.3
MLINKS+=	mitem_current.3 current_item.3
MLINKS+=	mitem_current.3 item_index.3
MLINKS+=	mitem_current.3 set_current_item.3
MLINKS+=	mitem_current.3 set_top_row.3
MLINKS+=	mitem_current.3 top_row.3
MLINKS+=	mitem_name.3 item_description.3
MLINKS+=	mitem_name.3 item_name.3
MLINKS+=	mitem_new.3 free_item.3
MLINKS+=	mitem_new.3 new_item.3
MLINKS+=	mitem_opts.3 item_opts.3
MLINKS+=	mitem_opts.3 item_opts_off.3
MLINKS+=	mitem_opts.3 item_opts_on.3
MLINKS+=	mitem_opts.3 set_item_opts.3
MLINKS+=	mitem_userptr.3 item_userptr.3
MLINKS+=	mitem_userptr.3 set_item_userptr.3
MLINKS+=	mitem_value.3 item_value.3
MLINKS+=	mitem_value.3 set_item_value.3
MLINKS+=	mitem_visible.3 item_visible.3

.include <bsd.own.mk>

LIBNCDIR?=	${BSDSRCDIR}/lib/libncurses
.include "${LIBNCDIR}/Makefile.inc"

CPPFLAGS+=	-I${NCSRCDIR}/ncurses -I${NCSRCDIR}/menu

.PATH: ${NCSRCDIR}/menu

SRCS+=		m_attribs.c
SRCS+=		m_cursor.c
SRCS+=		m_driver.c
SRCS+=		m_format.c
SRCS+=		m_global.c
SRCS+=		m_hook.c
SRCS+=		m_item_cur.c
SRCS+=		m_item_nam.c
SRCS+=		m_item_new.c
SRCS+=		m_item_opt.c
SRCS+=		m_item_top.c
SRCS+=		m_item_use.c
SRCS+=		m_item_val.c
SRCS+=		m_item_vis.c
SRCS+=		m_items.c
SRCS+=		m_new.c
SRCS+=		m_opts.c
SRCS+=		m_pad.c
SRCS+=		m_pattern.c
SRCS+=		m_post.c
SRCS+=		m_req_name.c
SRCS+=		m_scale.c
SRCS+=		m_spacing.c
SRCS+=		m_sub.c
SRCS+=		m_trace.c
SRCS+=		m_userptr.c
SRCS+=		m_win.c

GENERATED=	ncurses_def.h
CLEANFILES+=	${GENERATED}

beforedepend: ${GENERATED}

ncurses_def.h: ${NCSRCDIR}/include/MKncurses_def.sh \
    ${NCSRCDIR}/include/ncurses_defs
	AWK=${AWK:Q} ${MKSH} ${NCSRCDIR}/include/MKncurses_def.sh \
	    ${NCSRCDIR}/include/ncurses_defs >$@

HDRS=		menu/eti.h menu/menu.h
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
