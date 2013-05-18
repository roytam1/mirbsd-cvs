# $MirOS: src/share/i18n/esdb/Makefile,v 1.5 2006/09/07 19:00:32 tg Exp $
# $NetBSD: Makefile,v 1.4 2003/10/21 10:01:21 lukem Exp $

NOMAN=

.include <bsd.own.mk>

BINDIR?=	/usr/share/i18n/esdb

.SUFFIXES: .src .esdb

.src.esdb:
	${_MKTARGET_CREATE}
	${TOOL_MKESDB} -o $@ $>

XSUBDIR=	CP EUC EBCDIC ISO-2022 ISO-8859 ISO646 MISC UTF

.for i in ${XSUBDIR}
.  include "${.CURDIR}/$i/Makefile.inc"
.endfor

SUBDIR+= mkesdb
TOOL_MKESDB=${.CURDIR}/mkesdb/${__objdir}/mkesdb

# ----------------------------------------------------------------------
# esdb.{dir,alias}
#

esdb.dir: ${SRC_esdb.dir}
	${_MKTARGET_CREATE}
	cat $> | unexpand -a >$@

esdb.dir.db: esdb.dir
	${_MKTARGET_CREATE}
	${TOOL_MKESDB} -m -o $@ $>

esdb.alias: ${SRC_esdb.alias}
	${_MKTARGET_CREATE}
	cat $> | unexpand -a >$@

esdb.alias.db: esdb.alias
	${_MKTARGET_CREATE}
	${TOOL_MKESDB} -m -o $@ $>

FILES+=		esdb.dir esdb.dir.db esdb.alias esdb.alias.db
CLEANFILES+=	esdb.dir esdb.dir.db esdb.alias esdb.alias.db
FILESDIR:=	${BINDIR}

all: _SUBDIRUSE .WAIT ${TOOL_MKESDB} ${FILES}
realall: ${FILES}

${TOOL_MKESDB}:
	cd ${.CURDIR}/mkesdb && \
	    ${MAKE} CC=${HOSTCC:Q} CFLAGS=${HOSTCFLAGS:M*:Q}

.include <bsd.prog.mk>
