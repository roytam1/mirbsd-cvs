## Process this file with automake to produce Makefile.in
# $MirOS$
# Makefile for GNU CVS contributed sources.
# Do not use this makefile directly, but only from `../Makefile'.
# Copyright (C) 1986, 1987, 1988, 1989, 1990, 1991, 1992, 1993, 1994,
#               1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003
#               2004, 2005
#               Free Software Foundation, Inc.

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
	intro.doc

contrib_MANS = \
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
