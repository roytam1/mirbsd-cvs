# $MirOS: src/share/i18n/esdb/Makefile,v 1.3 2006/01/31 15:59:31 tg Exp $
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
	cat $> > $@
esdb.dir.db: esdb.dir
	${_MKTARGET_CREATE}
	${TOOL_MKESDB} -m -o $@ $>

esdb.alias: ${SRC_esdb.alias}
	${_MKTARGET_CREATE}
	cat $> > $@
esdb.alias.db: esdb.alias
	${_MKTARGET_CREATE}
	${TOOL_MKESDB} -m -o $@ $>

FILES+=		esdb.dir esdb.dir.db esdb.alias esdb.alias.db
CLEANFILES+=	esdb.dir esdb.dir.db esdb.alias esdb.alias.db
FILESDIR:=	${BINDIR}

all: _SUBDIRUSE .WAIT ${TOOL_MKESDB} ${FILES}
realall: ${FILES}

${TOOL_MKESDB}:
	cd ${.CURDIR}/mkesdb && ${MAKE}

.include <bsd.prog.mk>
