# $MirOS$

.include <bsd.own.mk>

NOMAN=		yes
_SMALL=		yes
_SRCDIR=	${BSDSRCDIR}/usr.sbin/isdn/isdnd
CPPFLAGS+=	-I${_SRCDIR} -I${_SRCDIR}/../isdnmonitor \
		-I${_SRCDIR}/../isdntel

.PATH:	${_SRCDIR}
.include "${_SRCDIR}/Makefile"
