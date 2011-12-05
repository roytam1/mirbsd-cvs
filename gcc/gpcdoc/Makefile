# $MirOS$

FILES!=		echo *.info

all clean cleandir depend includes install lint obj prereq tags:

install:
.for _i in ${FILES}
	${INSTALL} ${INSTALL_COPY} -o ${MANOWN} -g ${MANGRP} -m ${MANMODE} \
	    ${_i} ${DESTDIR}/usr/share/info/
.endfor

.include <bsd.own.mk>
