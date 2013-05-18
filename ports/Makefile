# $MirOS: ports/Makefile,v 1.14 2006/01/02 03:29:12 tg Exp $
# $OpenBSD: Makefile,v 1.43 2003/12/15 17:56:40 espie Exp $
# $FreeBSD: Makefile,v 1.36 1997/10/04 15:54:31 jkh Exp $
#-
# Copyright (c) 2004, 2005, 2006
#	The MirOS Project <miros-discuss@66h.42h.de>
#	and its contributors
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# Licensor offers the work "AS IS" and WITHOUT WARRANTY of any kind,
# express, or implied, to the maximum extent permitted by applicable
# law, without malicious intent or gross negligence; in no event may
# licensor, an author or contributor be held liable for any indirect
# or other damage, or direct damage except proven a consequence of a
# direct error of said person and intended use of this work, loss or
# other issues arising in any way out of its use, even if advised of
# the possibility of such damage or existence of a nontrivial bug.
#-
# For a complete list of people who contributed to MirPorts read the
# CVS ChangeLog, and the OpenBSD CVS ChangeLogs.
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
_CMD+=key='${key}'
.  endif
.  if defined(name)
_CMD+=maintainer='${name}'
.  endif
.  if defined(category)
_CMD+=category='${category}'
.  endif
.  if defined(maintainer)
_CMD+=maintainer='${maintainer}'
.  endif
SUBDIR != ${_CMD}
_MANUAL_SUBDIR=	yes
.elif defined(SUBDIRLIST)
SUBDIR != sed -e 's,[ 	]*\#.*,,' -e '/^[ 	]*$$/d' ${SUBDIRLIST}
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

${.CURDIR}/INDEX:
	@echo "Generating INDEX..."
	@USE_ICONV=port \
	    ${MAKE} describe ECHO_MSG="echo 1>&2" >${.CURDIR}/INDEX
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
	@egrep -i -- "${key}" ${.CURDIR}/INDEX | awk -F\| '{ printf("Port:\t%s\nPath:\t%s\nInfo:\t%s\nMaint:\t%s\nIndex:\t%s\nL-deps:\t%s\nB-deps:\t%s\nR-deps:\t%s\nArchs:\t%s\n\n", $$1, $$2, $$4, $$6, $$7, $$8, $$9, $$10, $$11); }'
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
	trap "rm -f $${_DONE_FILES}" 0 1 2 3 13 15; \
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
	if [[ -d /usr/mpkg/lib/X11/app-defaults ]]; then \
		${SUDO} mv /usr/mpkg/lib/X11/app-defaults/* \
		    /etc/X11/app-defaults/; \
		${SUDO} rmdir /usr/mpkg/lib/X11/app-defaults; \
	fi
	${SUDO} ln -sf /etc/X11/app-defaults /usr/mpkg/lib/X11/app-defaults
	env CC='${CC}' SHELL=${SHELL} MKSH=${MKSH} \
	    ${SUDO} /bin/sh ${.CURDIR}/Setup.sh

nfo: Setup.sh.nfo Setup.sh.htm

Setup.sh.man: Setup.sh.8
	${NROFF} -mdoc <$> >$@ || (rm -f $@; false)

Setup.sh.nfo: Setup.sh.man
	col -b <$> | sed "s!\$$!$$(printf \\r)!" >$@ || (rm -f $@; false)

Setup.sh.htm: Setup.sh.man
	(. ${BSDSRCDIR}/scripts/roff2htm; do_conversion Setup.sh 8) <$> >$@

CVSROOT?=/cvs
cvsup:
	cd ${.CURDIR} && cvs -Rqz3 -d ${CVSROOT} up -PAd

.PHONY: mirror-maker index search distfiles-update-locatedb \
	print-licences print-index portupgrade setup cvsup nfo
