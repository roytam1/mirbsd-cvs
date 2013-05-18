# $MirOS: src/lib/libncurses/Makefile.inc,v 1.8 2006/10/29 12:01:54 tg Exp $

# XXX should be defined elsewhere
AWK?=		/usr/bin/awk
NCSRCDIR=	${LIBNCDIR}/src

CPPFLAGS+=	-D'SYSTEM_NAME="${OSname}${OSrev}"' -DHAVE_CONFIG_H -DNDEBUG
CPPFLAGS+=	-D_XOPEN_SOURCE_EXTENDED -DXTSTRINGDEFINES
CPPFLAGS+=	-I. -I${NCSRCDIR}/include -I${NCSRCDIR}

CDIAGFLAGS+=		-Wno-redundant-decls
CFLAGS_lib_gen.o+=	-Wno-unused

HOSTCFLAGS?=	${CFLAGS}
HOSTLDFLAGS?=	${LDFLAGS}
HOSTCFLAGS+=	${CPPFLAGS} -I${.CURDIR}

NCMANPROCESS=	sed -e s,@DATADIR@,/usr/share, \
		    -e s,@TERMINFO@,/usr/share/terminfo, \
		    -e s,@NCURSES_OSPEED@,short, \
		    -e s,@CAPTOINFO@,captoinfo, \
		    -e s,@CLEAR@,clear, \
		    -e s,@INFOCMP@,infocmp, \
		    -e s,@INFOTOCAP@,infotocap, \
		    -e s,@TIC@,tic, \
		    -e s,@TOE@,toe, \
		    -e s,@TPUT@,tput, \
		    -e 's! 1M ! 1 !' -e 's!(1M)!(1)!g' \
		    -e 's! 3S ! 3 !' -e 's!(3S)!(3)!g' \
		    -e 's! 3X ! 3 !' -e 's!(3X)!(3)!g'

.for _i in ${NCMANSRCS}
MAN+=		${_i:S/.1$/.1tbl/:S/.1m$/.1tbl/:S/.3x$/.3tbl/}
CLEANFILES+=	${_i:S/.1$/.1tbl/:S/.1m$/.1tbl/:S/.3x$/.3tbl/}

${_i:S/.1$/.1tbl/:S/.1m$/.1tbl/:S/.3x$/.3tbl/}: ${NCSRCDIR}/man/${_i}
	${NCMANPROCESS} <$> >$@ || rm -f $@
.endfor

.ifdef LIB
afterinstall: afterinstall-liblinks

afterinstall-liblinks: .PHONY realinstall
	cd ${DESTDIR}${LIBDIR}; l=; for i in ${_LIBS}; do \
		[[ -e $$i ]] || continue; \
		for j in ${LIBLINKS}; do \
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
.endif
