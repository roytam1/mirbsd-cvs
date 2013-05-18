# $MirOS: ports/infrastructure/pkgtools/rtfm/Makefile,v 1.4 2007/09/23 20:56:29 bsiegert Exp $

MAN+=		bsd.port.mk.5 mirroring-ports.7 packages-specs.7 packages.7 \
		ports.7 cvs-distfiles.7 rcdb.3 pkgtools.conf.5

PORTSDIR?=	${.CURDIR}/../../..
.PATH: ${PORTSDIR}
.if exists(${PORTSDIR}/Setup.sh.8)
MAN+=		Setup.sh.8
.endif

MLINKS=		mirroring-ports.7 mirror-maker.7
MLINKS+=	rcdb.3 rcdb_open.3 rcdb.3 rcdb_close.3 rcdb.3 rcdb_lookup.3
MLINKS+=	rcdb.3 rcdb_write.3 rcdb.3 rcdb_modify.3 rcdb.3 rcdb_delete.3
MLINKS+=	rcdb.3 rcdb_retrieve.3 rcdb.3 rcdb_read.3 rcdb.3 rcdb_store.3

.include <bsd.prog.mk>
