# $MirOS: ports/Makefile,v 1.34 2009/02/24 17:58:44 bsiegert Exp $
# $OpenBSD: Makefile,v 1.43 2003/12/15 17:56:40 espie Exp $
# $FreeBSD: Makefile,v 1.36 1997/10/04 15:54:31 jkh Exp $
#-
# Copyright (c) 2004, 2005, 2006, 2007
#	The MirOS Project <miros-discuss@mirbsd.org>
#	and its contributors
#
# Provided that these terms and disclaimer and all copyright notices
# are retained or reproduced in an accompanying document, permission
# is granted to deal in this work without restriction, including un-
# limited rights to use, publicly perform, distribute, sell, modify,
# merge, give away, or sublicence.
#
# This work is provided "AS IS" and WITHOUT WARRANTY of any kind, to
# the utmost extent permitted by applicable law, neither express nor
# implied; without malicious intent or gross negligence. In no event
# may a licensor, author or contributor be held liable for indirect,
# direct, other damage, loss, or other issues arising in any way out
# of dealing in the work, even if advised of the possibility of such
# damage or existence of a defect, except proven that it results out
# of said person's immediate fault when using the work as intended.
#-
# For a complete list of people who contributed to MirPorts read the
# CVS ChangeLog, and the (historic, ancient) OpenBSD CVS ChangeLogs.
# For a list of MirOS Project members please read the documentation,
# it comes with a standard MirOS installation and is available via a
# CVSweb mirror (src/share/doc/legal/1stREAD) as well.
# All patches except forward ed(1) diffs are also covered by the li-
# cence of the file to be patched. Some of the files in the MirPorts
# Framework are covered by different terms of use. Ports are not co-
# vered by specific terms since they're too small to be worth it.


PKGPATH=
.if defined(key) || defined(name) || defined(category) || defined(author)

# set up subdirs from the index, assume it's up-to-date
_CMD=perl ${.CURDIR}/infrastructure/scripts/index-retrieve index='${.CURDIR}/INDEX'
.  if defined(key)
_CMD+=key=${key:Q}
.  endif
.  if defined(name)
_CMD+=maintainer=${name:Q}
.  endif
.  if defined(category)
_CMD+=category=${category:Q}
.  endif
.  if defined(maintainer)
_CMD+=maintainer=${maintainer:Q}
.  endif
SUBDIR!=	${_CMD}
_MANUAL_SUBDIR=	yes
.endif
.if defined(SUBDIRLIST)
SUBDIR!=	sed -e 's,[   ]*\#.*,,' -e '/^[       ]*$$/d' ${SUBDIRLIST}
_MANUAL_SUBDIR=	yes
.endif

PORTSTOP?=	yes

.if !make(setup) && !make(nfo)
.  include <bsd.port.subdir.mk>
.endif
.ifndef BSD_OWN_MK
.  include <bsd.own.mk>
.endif

index:
	@rm -f ${.CURDIR}/INDEX
	@${MAKE} ${.CURDIR}/INDEX
	@echo "$$(fgrep -c '' INDEX) ($$(fgrep -c '(broken)' INDEX) broken)"

${.CURDIR}/INDEX:
	@echo "Generating INDEX..."
	@${MAKE} USE_ICONV=port USE_CCACHE=No OStype=MirBSD OSNAME=MirBSD \
	    OSver=10.160 MACHINE_OS=BSD MACHINE=i386 MACHINE_ARCH=i386 \
	    USE_COMPILER=system USE_CCACHE=no \
	    describe ECHO_MSG="echo 1>&2" >${.CURDIR}/INDEX
	@echo "Done."

print-index:	${.CURDIR}/INDEX
	@awk -F\| '{ printf("Port:\t%s\nPath:\t%s\nInfo:\t%s\nMaint:\t%s\nIndex:\t%s\nL-deps:\t%s\nB-deps:\t%s\nR-deps:\t%s\n\n", $$1, $$2, $$4, $$7, $$8, $$9, $$10, $$11); }' < ${.CURDIR}/INDEX

print-licences: ${.CURDIR}/INDEX
	@printf "Port                                    PC PF DC DF Maint\n"
	@awk -F\| '{printf("%-40.39s%-3.2s%-3.2s%-3.2s%-3.2s%-25.25s\n",$$2,$$13,$$14,$$15,$$16,$$7);}' < ${.CURDIR}/INDEX

search:	${.CURDIR}/INDEX
.if !defined(key) && !defined(name)
	@echo "The search target requires a keyword or name parameter,"
	@echo "e.g.: \"mmake search key=somekeyword\" \"mmake search name=somename\""
.else
. if defined(key)
	@egrep -i -- ${key:Q} ${.CURDIR}/INDEX | awk -F\| '{ printf("Port:\t%s\nPath:\t%s\nInfo:\t%s\nMaint:\t%s\nIndex:\t%s\nL-deps:\t%s\nB-deps:\t%s\nR-deps:\t%s\nArchs:\t%s\n\n", $$1, $$2, $$4, $$6, $$7, $$8, $$9, $$10, $$11); }'
. else
	@awk -F\| '$$1 ~ /${name}/ { printf("Port:\t%s\nPath:\t%s\nInfo:\t%s\nMaint:\t%s\nIndex:\t%s\nL-deps:\t%s\nB-deps:\t%s\nR-deps:\t%s\nArchs:\t%s\n\n", $$1, $$2, $$4, $$6, $$7, $$8, $$9, $$10, $$11); }' ${.CURDIR}/INDEX
. endif
.endif


MIRROR_MK?= ${.CURDIR}/Distfiles/Makefile

mirror-maker:
	@mkdir -p ${MIRROR_MK:H}
# Indirection needed for broken OSes that don't grok this exec
	@echo "EXEC=exec" >${MIRROR_MK}
	@echo "default:: ftp cdrom" >>${MIRROR_MK}
	@echo ".PHONY: default all ftp cdrom" >>${MIRROR_MK}
	@_DONE_FILES=$$(mktemp /tmp/depends.XXXXXXXXX|| exit 1); \
	export _DONE_FILES; \
	trap "rm -f $${_DONE_FILES}" 0 1 2 3 5 13 15; \
	${MAKE} fetch-makefile \
		ECHO_MSG='echo >&2' \
		>>${MIRROR_MK}

homepages.html:
	@echo '<html><ul>' >$@
	@${MAKE} homepage-links ECHO_MSG='echo >&2' >>$@
	@echo '</ul></html>' >>$@

DISTFILES_DB?=${.CURDIR}/infrastructure/db/locate.database

distfiles-update-locatedb:
	@PORTSDIR=${.CURDIR} ${SHELL} \
	    ${.CURDIR}/infrastructure/scripts/distfiles-update-locatedb \
	    ${DISTFILES_DB}

bulk-build:
	if [[ ! -e ${.CURDIR}/Bulk ]]; then \
		${SUDO} mkdir -m 0775 Bulk; \
	fi
	if [[ ! -e ${.CURDIR}/Logs ]]; then \
		${SUDO} mkdir -m 0775 Logs; \
	fi
	env BIN_PACKAGES=Yes TRUST_PACKAGES=Yes BULK=Yes BATCH=Yes \
	    ${MAKE} package clean 2>&1 | \
	    perl ${.CURDIR}/infrastructure/scripts/portslogger ${.CURDIR}/Logs

portupgrade: index
	@PORTSDIR=${.CURDIR} ${SHELL} \
	    ${.CURDIR}/infrastructure/scripts/out-of-date

# Yes, this does hardcode /bin/sh and that's correct.
setup: Setup.sh
	@echo 'Use "mmake nfo" to generate documentation!'
	@sleep 3
	if [[ ! -e ${.CURDIR}/Distfiles ]]; then \
		${SUDO} mkdir -m 0775 Distfiles; \
	fi
	if [[ ! -e ${.CURDIR}/Packages ]]; then \
		${SUDO} mkdir -m 0775 Packages; \
	fi
	print '/@@local/d\ni\n    usr\n\tmpkg\n.\n%p\nQ' | \
	    ed -s ${.CURDIR}/infrastructure/templates/fake.mtree | \
	    ${SUDO} mtree -U -e -d -n -p /
.if exists(/etc/X11/app-defaults)
	[[ -L /usr/mpkg/lib/X11/app-defaults ]] || \
	    if [[ -d /usr/mpkg/lib/X11/app-defaults ]]; then \
		${SUDO} mv /usr/mpkg/lib/X11/app-defaults/* \
		    /etc/X11/app-defaults/ || true; \
		${SUDO} rmdir /usr/mpkg/lib/X11/app-defaults; \
	fi
	${SUDO} ln -sf /etc/X11/app-defaults /usr/mpkg/lib/X11/app-defaults
.endif
	${SUDO} rm -rf /usr/mpkg/.sst /etc/.mirports.test.*
	(echo "Policy: /usr/bin/env, Emulation: native"; \
	    cat ${.CURDIR}/infrastructure/templates/systrace.filter) \
	    | ${SUDO} dd of=/usr/mpkg/.sst
	printf '%s\n%s\n%s\n%s\n%s\nwq\n' '%g!PORTSDIR!d' '%g!PKG_TMPDIR!d' \
	    '%g!TMPDIR!s!..TMPDIR.!/etc/.mirports.test.*!g' '%g!DISTDIR!d' \
	    '%g!WRKDIR!s!..WRKDIR.!/usr/mpkg!g' | ${SUDO} ed -s /usr/mpkg/.sst
	/bin/systrace -e -i -a -f /usr/mpkg/.sst /usr/bin/env CC=${CC:Q} \
	    SHELL=${MKSH:Q} MKSH=${MKSH:Q} NO_SYSTRACE=bootstrap \
	    ${SUDO} /bin/sh ${.CURDIR}/Setup.sh -T
	${SUDO} rm -rf /usr/mpkg/.sst /etc/.mirports.test.*

nfo: Setup.sh.nfo
.if exists(${BSDSRCDIR}/scripts/roff2htm)
nfo: Setup.sh.htm
.endif

Setup.sh.man: Setup.sh.8
	${NROFF} -mdoc <$> >$@ || (rm -f $@; false)

Setup.sh.nfo: Setup.sh.man
	col -b <$> | sed "s!\$$!$$(printf \\r)!" >$@ || (rm -f $@; false)

Setup.sh.htm: Setup.sh.man
	(. ${BSDSRCDIR}/scripts/roff2htm; do_conversion Setup.sh 8) <$> >$@

.if exists(/cvs/CVSROOT/config)
CVSROOT?=	/cvs
.endif
CVSROOT?=	${_MIROS_ANONCVS}

cvsup:
	cd ${.CURDIR} && umask 002 && cvs -Rqz3 -d ${CVSROOT} up -PAd

.PHONY: mirror-maker index search distfiles-update-locatedb \
	print-licences print-index portupgrade setup cvsup nfo
