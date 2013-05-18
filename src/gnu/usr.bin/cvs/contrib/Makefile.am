## Process this file with automake to produce Makefile.in
# $MirOS: src/gnu/usr.bin/cvs/contrib/Makefile.am,v 1.3 2005/04/19 20:58:12 tg Exp $
# Makefile for GNU CVS contributed sources.
# Do not use this makefile directly, but only from `../Makefile'.
#
# Copyright (C) 1986-2005 The Free Software Foundation, Inc.
#
# Portions Copyright (C) 1998-2005 Derek Price, Ximbiot <http://ximbiot.com>,
#                                  and others.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

contribdir = $(pkgdatadir)/contrib

contrib_SCRIPTS = \
	clmerge \
	cln_hist \
	commit_prep \
	cvs2vendor \
	cvs_acls \
	debug_check_log \
	log \
	log_accum \
	mfpipe \
	newcvsroot \
	pvcs2rcs \
	rcs-to-cvs \
	rcs2log \
	rcslock \
	sandbox_status \
	sccs2rcs \
	validate_repo

contrib_DATA = \
	README \
	intro.doc \
	rcs-5.7-commitid.patch

contrib_MANS = \
	rcs2log.1 \
	sandbox_status.man

EXTRA_DIST = \
	$(contrib_DATA) \
	$(contrib_MANS) \
	cvs2vendor.sh \
	sandbox_status.sh \
	cvshelp.man \
	cvs_acls.html \
	debug_check_log.sh \
	descend.sh \
	descend.man \
	dirfns.shar \
	newcvsroot.sh \
	rcs-5.7-commitid.patch \
	rcs-to-cvs.sh \
	rcs2log.sh \
	rcs2sccs.sh

CLEANFILES = $(contrib_SCRIPTS)

SUFFIXES = .sh

.sh:
	rm -f $@
	cp $< $@
	chmod +x $@

# for backwards compatibility with the old makefiles
realclean: maintainer-clean
.PHONY: realclean
