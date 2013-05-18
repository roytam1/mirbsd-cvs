# $MirOS: src/lib/libform/Makefile,v 1.5 2007/05/17 18:38:32 tg Exp $

LIB=		form
DPADD+=		${LIBCURSES}
LDADD+=		-lcurses
LIBLINKS=	formw
SHLIB_VERSION?=	6.0

NCMANSRCS+=	form.3x
NCMANSRCS+=	form_cursor.3x
NCMANSRCS+=	form_data.3x
NCMANSRCS+=	form_driver.3x
NCMANSRCS+=	form_field.3x
NCMANSRCS+=	form_field_attributes.3x
NCMANSRCS+=	form_field_buffer.3x
NCMANSRCS+=	form_field_info.3x
NCMANSRCS+=	form_field_just.3x
NCMANSRCS+=	form_field_new.3x
NCMANSRCS+=	form_field_opts.3x
NCMANSRCS+=	form_field_userptr.3x
NCMANSRCS+=	form_field_validation.3x
NCMANSRCS+=	form_fieldtype.3x
NCMANSRCS+=	form_hook.3x
NCMANSRCS+=	form_new.3x
NCMANSRCS+=	form_new_page.3x
NCMANSRCS+=	form_opts.3x
NCMANSRCS+=	form_page.3x
NCMANSRCS+=	form_post.3x
NCMANSRCS+=	form_requestname.3x
NCMANSRCS+=	form_userptr.3x
NCMANSRCS+=	form_win.3x

MLINKS+=	form_cursor.3 pos_form_cursor.3
MLINKS+=	form_data.3 data_ahead.3
MLINKS+=	form_data.3 data_behind.3
MLINKS+=	form_field.3 field_count.3
MLINKS+=	form_field.3 form_fields.3
MLINKS+=	form_field.3 move_field.3
MLINKS+=	form_field.3 set_form_fields.3
MLINKS+=	form_field_attributes.3 field_back.3
MLINKS+=	form_field_attributes.3 field_fore.3
MLINKS+=	form_field_attributes.3 field_pad.3
MLINKS+=	form_field_attributes.3 set_field_back.3
MLINKS+=	form_field_attributes.3 set_field_fore.3
MLINKS+=	form_field_attributes.3 set_field_pad.3
MLINKS+=	form_field_buffer.3 field_buffer.3
MLINKS+=	form_field_buffer.3 field_status.3
MLINKS+=	form_field_buffer.3 set_field_buffer.3
MLINKS+=	form_field_buffer.3 set_field_status.3
MLINKS+=	form_field_buffer.3 set_max_field.3
MLINKS+=	form_field_info.3 dynamic_field_info.3
MLINKS+=	form_field_info.3 field_info.3
MLINKS+=	form_field_just.3 field_just.3
MLINKS+=	form_field_just.3 set_field_just.3
MLINKS+=	form_field_new.3 dup_field.3
MLINKS+=	form_field_new.3 free_field.3
MLINKS+=	form_field_new.3 link_field.3
MLINKS+=	form_field_new.3 new_field.3
MLINKS+=	form_field_opts.3 field_opts.3
MLINKS+=	form_field_opts.3 field_opts_off.3
MLINKS+=	form_field_opts.3 field_opts_on.3
MLINKS+=	form_field_opts.3 set_field_opts.3
MLINKS+=	form_field_userptr.3 field_userptr.3
MLINKS+=	form_field_userptr.3 set_field_userptr.3
MLINKS+=	form_field_validation.3 field_arg.3
MLINKS+=	form_field_validation.3 field_type.3
MLINKS+=	form_field_validation.3 set_field_type.3
MLINKS+=	form_fieldtype.3 free_fieldtype.3
MLINKS+=	form_fieldtype.3 link_fieldtype.3
MLINKS+=	form_fieldtype.3 new_fieldtype.3
MLINKS+=	form_fieldtype.3 set_fieldtype_arg.3
MLINKS+=	form_fieldtype.3 set_fieldtype_choice.3
MLINKS+=	form_hook.3 field_init.3
MLINKS+=	form_hook.3 field_term.3
MLINKS+=	form_hook.3 form_init.3
MLINKS+=	form_hook.3 form_term.3
MLINKS+=	form_hook.3 set_field_init.3
MLINKS+=	form_hook.3 set_field_term.3
MLINKS+=	form_hook.3 set_form_init.3
MLINKS+=	form_hook.3 set_form_term.3
MLINKS+=	form_new.3 free_form.3
MLINKS+=	form_new.3 new_form.3
MLINKS+=	form_new_page.3 new_page.3
MLINKS+=	form_new_page.3 set_new_page.3
MLINKS+=	form_opts.3 form_opts_off.3
MLINKS+=	form_opts.3 form_opts_on.3
MLINKS+=	form_opts.3 set_form_opts.3
MLINKS+=	form_page.3 current_field.3
MLINKS+=	form_page.3 field_index.3
MLINKS+=	form_page.3 set_current_field.3
MLINKS+=	form_page.3 set_form_page.3
MLINKS+=	form_post.3 post_form.3
MLINKS+=	form_post.3 unpost_form.3
MLINKS+=	form_requestname.3 form_request_by_name.3
MLINKS+=	form_requestname.3 form_request_name.3
MLINKS+=	form_userptr.3 set_form_userptr.3
MLINKS+=	form_win.3 form_sub.3
MLINKS+=	form_win.3 scale_form.3
MLINKS+=	form_win.3 set_form_sub.3
MLINKS+=	form_win.3 set_form_win.3

.include <bsd.own.mk>

LIBNCDIR?=	${BSDSRCDIR}/lib/libncurses
.include "${LIBNCDIR}/Makefile.inc"

CPPFLAGS+=	-I${NCSRCDIR}/ncurses -I${NCSRCDIR}/form -I${NCSRCDIR}/menu

.PATH: ${NCSRCDIR}/form

SRCS+=		f_trace.c
SRCS+=		fld_arg.c
SRCS+=		fld_attr.c
SRCS+=		fld_current.c
SRCS+=		fld_def.c
SRCS+=		fld_dup.c
SRCS+=		fld_ftchoice.c
SRCS+=		fld_ftlink.c
SRCS+=		fld_info.c
SRCS+=		fld_just.c
SRCS+=		fld_link.c
SRCS+=		fld_max.c
SRCS+=		fld_move.c
SRCS+=		fld_newftyp.c
SRCS+=		fld_opts.c
SRCS+=		fld_pad.c
SRCS+=		fld_page.c
SRCS+=		fld_stat.c
SRCS+=		fld_type.c
SRCS+=		fld_user.c
SRCS+=		frm_cursor.c
SRCS+=		frm_data.c
SRCS+=		frm_def.c
SRCS+=		frm_driver.c
SRCS+=		frm_hook.c
SRCS+=		frm_opts.c
SRCS+=		frm_page.c
SRCS+=		frm_post.c
SRCS+=		frm_req_name.c
SRCS+=		frm_scale.c
SRCS+=		frm_sub.c
SRCS+=		frm_user.c
SRCS+=		frm_win.c
SRCS+=		fty_alnum.c
SRCS+=		fty_alpha.c
SRCS+=		fty_enum.c
SRCS+=		fty_int.c
SRCS+=		fty_ipv4.c
SRCS+=		fty_num.c
SRCS+=		fty_regex.c

GENERATED=	ncurses_def.h
CLEANFILES+=	${GENERATED}

beforedepend: ${GENERATED}

ncurses_def.h: ${NCSRCDIR}/include/MKncurses_def.sh \
    ${NCSRCDIR}/include/ncurses_defs
	AWK=${AWK:Q} ${MKSH} ${NCSRCDIR}/include/MKncurses_def.sh \
	    ${NCSRCDIR}/include/ncurses_defs >$@

HDRS=		form/form.h
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
