# $MirOS: src/share/termtypes/Makefile,v 1.3 2006/06/16 22:55:10 tg Exp $
# $OpenBSD: Makefile,v 1.15 2000/02/17 19:58:34 millert Exp $
#
# Take termcap/terminfo master file and generate termcap/terminfo .db files
# master: http://catb.org/~esr/terminfo/termtypes.master.gz
#
# millert@openbsd says we don't use the master but the version from ncurses
# since it's more actively maintained.

MAN=		termcap.5
CLEANFILES+=	terminfo.src termcap.src terminfo.db termcap.db

all: terminfo.db termcap.db

terminfo.src: termtypes.master
	${TIC} -I -x ${.ALLSRC} | sed \
	    -e 's,/usr/share/lib/tabset,/usr/share/tabset,g' \
	    -e 's,/usr/lib/tabset,/usr/share/tabset,g' \
	    >$@
	@if [ ! -s ${.TARGET} ]; then \
	    echo ${.TARGET} is zero length!  You need to update ${TIC} ;\
	    rm -f ${.TARGET} ;\
	    exit 1 ;\
	else case $$(sed 1q ${.TARGET}) in \
	    Usage*) echo ${.TARGET} is corrupt!  You need to update ${TIC} ;\
		    rm -f ${.TARGET} ;\
		    exit 1 ;;\
	    esac ;\
	fi

terminfo.db: terminfo.src
	cap_mkdb -cif terminfo terminfo.src

termcap.src: termtypes.master
	${TIC} -C -x ${.ALLSRC} | sed \
	    -e 's,/usr/share/lib/tabset,/usr/share/tabset,g' \
	    -e 's,/usr/lib/tabset,/usr/share/tabset,g' \
	    > ${.TARGET}
	@if [ ! -s ${.TARGET} ]; then \
	    echo ${.TARGET} is zero length!  You need to update ${TIC} ;\
	    rm -f ${.TARGET} ;\
	    exit 1 ;\
	else case $$(sed 1q ${.TARGET}) in \
	    Usage*) echo ${.TARGET} is corrupt!  You need to update ${TIC} ;\
		    rm -f ${.TARGET} ;\
		    exit 1 ;;\
	    esac ;\
	fi

termcap.db: termcap.src
	cap_mkdb -cf termcap termcap.src

realinstall:
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 terminfo.db \
	     ${DESTDIR}${BINDIR}/misc/terminfo.db
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 termcap.db \
	     ${DESTDIR}${BINDIR}/misc/termcap.db
	${INSTALL} ${INSTALL_COPY} -o ${BINOWN} -g ${BINGRP} -m 444 termcap.src \
	     ${DESTDIR}${BINDIR}/misc/termcap
	ln -fs ${BINDIR}/misc/termcap ${DESTDIR}/etc/termcap

.include <bsd.prog.mk>

# Use the tic we just built if possible
.if ${CROSS_MODE:L} == "yes"
TIC=	/usr/bin/tic
.elif exists(${.CURDIR}/../../usr.bin/tic/${__objdir}/tic)
TIC=	${.CURDIR}/../../usr.bin/tic/${__objdir}/tic
.elif exists(../../usr.bin/tic/tic)
TIC=	../../usr.bin/tic/tic
.else
TIC=	/usr/bin/tic
.endif
