# $MirOS: src/share/mk/bsd.sys.mk,v 1.11 2007/03/19 22:57:43 tg Exp $
# $OpenBSD: bsd.sys.mk,v 1.8 2000/07/06 23:12:41 millert Exp $
# $NetBSD: bsd.sys.mk,v 1.2 1995/12/13 01:25:07 cgd Exp $

.if !defined(BSD_SYS_MK)
BSD_SYS_MK=1

CPPFLAGS+=	-idirafter ${.CURDIR}

# The following is only wanted for source tree builds, not MirPorts
.ifndef TRUEPREFIX

.  if !defined(EXPERIMENTAL)
CFLAGS+=	-Werror
.    if !defined(BSD_CFWRAP_MK) && !make(depend)
CC:=		env GCC_HONOUR_COPTS=2 ${CC}
.    endif
.  endif

.  if defined(DESTDIR)
CPPFLAGS+=	-nostdinc -isystem ${DESTDIR}/usr/include
CXXFLAGS+=	-isystem ${DESTDIR}/usr/include/gxx \
		-isystem ${DESTDIR}/usr/include/gxx/${OStriplet} \
		-isystem ${DESTDIR}/usr/include/gxx/backward
.  endif

.  if defined(PARALLEL)
# Lex
.l:
	${LEX.l} -o${.TARGET:R}.yy.c ${.IMPSRC}
	${LINK.c} -o ${.TARGET} ${.TARGET:R}.yy.c ${LDLIBS} -ll
	rm -f ${.TARGET:R}.yy.c
.l.c:
	${LEX.l} -o${.TARGET} ${.IMPSRC}
.l.o:
	${LEX.l} -o${.TARGET:R}.yy.c ${.IMPSRC}
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -o ${.TARGET} ${.TARGET:R}.yy.c
	rm -f ${.TARGET:R}.yy.c

# Yacc
.y:
	${YACC.y} -b ${.TARGET:R} ${.IMPSRC}
	${LINK.c} -o ${.TARGET} ${.TARGET:R}.tab.c ${LDLIBS}
	rm -f ${.TARGET:R}.tab.c
.y.c:
	${YACC.y} -b ${.TARGET:R} ${.IMPSRC}
	mv ${.TARGET:R}.tab.c ${.TARGET}
.y.o:
	${YACC.y} -b ${.TARGET:R} ${.IMPSRC}
	${COMPILE.c} ${CFLAGS_${.TARGET}:M*} -o ${.TARGET} ${.TARGET:R}.tab.c
	rm -f ${.TARGET:R}.tab.c
.  endif

.endif

.endif
