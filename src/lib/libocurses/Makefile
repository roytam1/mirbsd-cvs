# $MirOS: src/lib/libocurses/Makefile,v 1.3 2005/10/21 11:02:49 tg Exp $
# $OpenBSD: Makefile,v 1.8 2002/06/24 18:03:30 tholo Exp $

#CPPFLAGS+=	-DTFILE=\"/dev/ttyp0\"
CPPFLAGS+=	-D_CURSES_PRIVATE
CPPFLAGS+=	-DCM_N -DCM_GT -DCM_B -DCM_D
SHLIB_VERSION?=	7.0
LIB=	ocurses
SRCS=	addbytes.c addch.c addnstr.c box.c clear.c clrtobot.c clrtoeol.c \
	cr_put.c ctrace.c cur_hash.c curses.c delch.c deleteln.c delwin.c \
	erase.c fullname.c getch.c getstr.c id_subwins.c idlok.c initscr.c \
	insch.c insertln.c longname.c move.c mvwin.c newwin.c overlay.c \
	overwrite.c printw.c putchar.c refresh.c scanw.c scroll.c setterm.c \
	standout.c toucholap.c touchwin.c tscroll.c tstp.c tty.c unctrl.c
SRCS+=	termcap.c tgoto.c tputs.c
MAN=	ocurses.3 otermcap.3

.if make(install)
SUBDIR+= PSD.doc
.endif

includes:
	-cd ${.CURDIR}; cmp -s curses.h ${DESTDIR}/usr/include/ocurses.h || \
	    ${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 \
	    curses.h ${DESTDIR}/usr/include/ocurses.h

.include <bsd.own.mk>

# Link libotermcap to libocurses for programs that need full compatibility
# with the old termcap behavior
afterinstall:
	cd ${DESTDIR}${LIBDIR}; l=; for i in ${_LIBS}; do \
		[[ -e $$i ]] || continue; \
		for j in otermcap; do \
			k=$$(print $$i | sed "s/${LIB}/$$j/"); \
			case $$i { \
			(*.a|*.la) \
				ln -f $$i $$k ;; \
			(*.so.*) \
				rm -f $$k; \
				if [[ -z $$l ]]; then \
					print 'GROUP(-l${LIB})' >$$k; \
					chown ${BINOWN}:${BINGRP} $$k; \
					chmod ${NONBINMODE} $$k; \
					l=$$k; \
				else \
					ln -f $$l $$k; \
				fi ;; \
			(*) \
				print "warning: cannot handle '$$i'" ;; \
			} \
		done; \
	done

.include <bsd.lib.mk>
