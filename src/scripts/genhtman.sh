#!/bin/ksh
# $MirOS: src/scripts/genhtman.sh,v 1.1 2005/03/06 16:08:16 tg Exp $
#-
# Copyright (c) 2005
#	Thorsten "mirabile" Glaser <tg@66h.42h.de>
#
# Licensee is hereby permitted to deal in this work without restric-
# tion, including unlimited rights to use, publicly perform, modify,
# merge, distribute, sell, give away or sublicence, provided all co-
# pyright notices above, these terms and the disclaimer are retained
# in all redistributions or reproduced in accompanying documentation
# or other materials provided with binary redistributions.
#
# Licensor hereby provides this work "AS IS" and WITHOUT WARRANTY of
# any kind, expressed or implied, to the maximum extent permitted by
# applicable law, but with the warranty of being written without ma-
# licious intent or gross negligence; in no event shall licensor, an
# author or contributor be held liable for any damage, direct, indi-
# rect or other, however caused, arising in any way out of the usage
# of this work, even if advised of the possibility of such damage.
#-
# Build the HTML format manual pages. This is part of the MirOS con-
# tribuional and base system release process.

print XXX not ported
exit 1

# for a in papers psd smm usd; do (cd papers; for x in $a.*; do (cd ../man$(print $a|tr '[:lower:]' '[:upper:]'); ln -s ../papers/$x ${x#$a.}); done); done                                                                       


...:
	mkdir -p ${MYDESTDIR}/htman || ${SUDO} mkdir -p ${MYDESTDIR}/htman
	cd ${.CURDIR}/etc && exec ${MAKE} htman RELEASEDIR=${MYRELDIR} \
	    DESTDIR=${MYDESTDIR}/htman BASEDESTDIR=${MYDESTDIR}/base

htman:
	@echo "Building HTML format manual pages."
	${SHELL} -c ". ${BSDSRCDIR}/scripts/man2htm; \
	    convert_all ${BASEDESTDIR}/usr/share/man ${DESTDIR}"
	@echo "Building ASCII to HTML format papers."
	mkdir -p ${DESTDIR}/papers
	-rm -rf ${BSDOBJDIR}/htman
.for _i in papers psd smm usd
	mkdir -p ${BSDOBJDIR}/htman/${_i}
	( cd ${BSDOBJDIR}/htman/${_i} \
	    && lndir ${BASEDESTDIR}/usr/share/doc/${_i} \
	    && ${MAKE} )
	[[ ! -e ${BSDOBJDIR}/htman/${_i}/Title.txt ]] \
	    || ${SHELL} -c ". ${BSDSRCDIR}/scripts/man2htm; \
	    output_header Title ${_i:U}; \
	    do_convert <${BSDOBJDIR}/htman/${_i}/Title.txt; \
	    output_footer" >${DESTDIR}/papers/${_i}-Title.htm
	[[ ! -e ${BSDOBJDIR}/htman/${_i}/contents.txt ]] \
	    || ${SHELL} -c ". ${BSDSRCDIR}/scripts/man2htm; \
	    output_header Contents ${_i:U}; \
	    do_convert <${BSDOBJDIR}/htman/${_i}/contents.txt; \
	    output_footer" >${DESTDIR}/papers/${_i}-contents.htm
	for f in ${BSDOBJDIR}/htman/${_i}/*/paper.txt; do \
		t=$$(print "$$f" | sed \
		    -e 's#${BSDOBJDIR}/htman/${_i}/##' \
		    -e 's#/paper.txt##'); \
		${SHELL} -c ". ${BSDSRCDIR}/scripts/man2htm; \
		    output_header $$t ${_i:U}; \
		    do_convert <$$f; \
		    output_footer" >${DESTDIR}/papers/${_i}.$$t.htm; \
	done
.endfor
	@echo "============================================================"
	@echo "Checking files:"
	@echo ""
	-cd ${.CURDIR}/../distrib/lists/htman && RELEASEDIR="${RELEASEDIR}" \
	    DESTDIR="${DESTDIR}" ${SHELL} ${BSDSRCDIR}/scripts/checkflist
	@echo "============================================================"
.  ifdef WAIT_CHECKFLIST
	@read a?'Press Return to continue...'
.  endif
	-cd ${.CURDIR}/../distrib/lists/htman && RELEASEDIR="${RELEASEDIR}" \
	    DESTDIR="${DESTDIR}" ${SUDO} ${SHELL} \
	    ${BSDSRCDIR}/scripts/maketars ${OSrev}
	-cd ${RELEASEDIR}; md5 htman${OSrev}.ngz | ${SUDO} tee -a MD5; \
	    cksum htman${OSrev}.ngz | ${SUDO} tee -a CKSUM

