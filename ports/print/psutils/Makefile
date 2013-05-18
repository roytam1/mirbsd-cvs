# $MirOS: ports/print/psutils/Makefile,v 1.4 2006/08/10 18:17:33 tg Exp $
# $OpenBSD: Makefile,v 1.18 2004/02/21 01:20:09 pvalchev Exp $

COMMENT=			manipulating PostScript documents
DISTNAME=		psutils-p17
PKGNAME=		psutils-1.17-2
CATEGORIES=		print
MASTER_SITES=   	ftp://ftp.tardis.ed.ac.uk/users/ajcd/
HOMEPAGE=		http://gershwin.ens.fr/vdaniel/Doc-Locale/Outils-Gnu-Linux/PsUtils/

PERMIT_PACKAGE_CDROM=	Yes
PERMIT_PACKAGE_FTP=	Yes
PERMIT_DISTFILES_CDROM=	Yes
PERMIT_DISTFILES_FTP=	Yes

WRKDIST=		${WRKDIR}/psutils

FLAVORS=		a3 a4 a5 b5 executive folio ledger legal \
			letter p10x14 quarto statement tabloid
FLAVOR?=		a4

POSSIBLE_SIZES=		${FLAVORS:L:S/p10x14/10x14/}
PAPERSIZE=		${FLAVOR:L:S/p10x14/10x14/}

.undef PP
.for _i in ${POSSIBLE_SIZES}
# This is weird but used to force evaluation
PT:=			${_i}
.  if ${PT} == ${PAPERSIZE}
PP:=			${PT}
.  endif
.endfor

.ifndef PP
ERRORS+="Fatal: invalid value for PAPERSIZE: \"${PAPERSIZE}\"" \
	"   Possible values are:  A3, A4 (default), A5, B5, letter, legal," \
	"   ledger, tabloid, statement, executive, folio, quarto, and 10x14."
.endif
EXTRA_MAKE_FLAGS=	\
			BINDIR=${PREFIX}/bin \
			INCLUDEDIR=${PREFIX}/share/psutils \
			MANDIR=${PREFIX}/man/man1
EXTRA_FAKE_FLAGS=	\
			BINDIR=${WRKINST}${PREFIX}/bin \
			INCLUDEDIR=${WRKINST}${PREFIX}/share/psutils \
			MANDIR=${WRKINST}${PREFIX}/man/man1
EXTRA_XAKE_FLAGS=	PERL=/usr/bin/perl PAPER=${PP}
MAKE_FILE=		Makefile.unix
CPPFLAGS+=		-DPAPER=\"${PP}\" -DUNIX

NO_REGRESS=	Yes

.include <bsd.port.mk>
