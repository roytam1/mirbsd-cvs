## Process this file with automake to produce Makefile.in
# $MirOS$
# Makefile for library files used by GNU CVS.
# Copyright (C) 1986, 1987, 1988, 1989, 1990, 1991, 1992, 1993, 1994,
#               1995, 1996, 1997, 1998, 1999, 2000, 2001, 2002, 2003
#               Free Software Foundation, Inc.

# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

noinst_LIBRARIES = libcvs.a

# Should look into unifying regular expression matching in CVS
# with the diff library (perhaps to have the caller, CVS, do the
# matching?)
libcvs_a_SOURCES = \
	md5.c \
	sighandle.c \
	system.h \
	wait.h \
	xselect.h \
	xtime.h
## Because @LIBOBJS@ is included below and AC_LIBOBJ is sometimes called on
## these files from configure.in, automake automatically knows about many of
## the *.c files in this directory.
libcvs_a_LIBADD = \
	@LIBOBJS@ \
	@ALLOCA@



## Zero some variables so Automake will allow us to use += on them.
BUILT_SOURCES =
MOSTLYCLEANFILES =
MAINTAINERCLEANFILES =
TESTS =
check_PROGRAMS =

EXTRA_DIST = \
	test-getdate.sh

## For GNULIB's allocsa module.
libcvs_a_SOURCES += allocsa.h allocsa.c
EXTRA_DIST += allocsa.valgrind

## For GNULIB's dirname module.
libcvs_a_SOURCES += basename.c dirname.c dirname.h stripslash.c

## For GNULIB's error module.
##
## This module isn't fully imported since GNULIB's error.c would conflict with
## src/error.c (which knows how to send error messages over the network).  We
## don't compile error.c into libcvs on purpose.  It can get compiled later as
## part of the getdate test program,
libcvs_a_SOURCES += error.h

## For GNULIB's exit module.
libcvs_a_SOURCES += exit.h

## For GNULIB's exitfail module.
libcvs_a_SOURCES += exitfail.h exitfail.c

## For GNULIB's getdate module.
libcvs_a_SOURCES += getdate.h getdate.y
## CVS test scripts for getdate.
TESTS += test-getdate.sh
MOSTLYCLEANFILES += getdate-expected getdate-got getdate.diff
# Program required by test-getdate.sh for testing getdate.y.
check_PROGRAMS += getdate
getdate_SOURCES = \
	allocsa.c \
	error.c \
	exitfail.c \
	exitfail.h \
	getdate.y \
	gettime.c \
	xalloc-die.c \
	xalloc.h \
	xmalloc.c 
## This source file was added only for the getdate test program when compiled
## with GNULIB's error.c.
getdate_SOURCES += \
	progname.c
getdate_CPPFLAGS = -DTEST
getdate_LDADD = \
	@LIBOBJS@ \
	@ALLOCA@ \
	$(LIB_CLOCK_GETTIME) \
	$(LIBINTL)

## For GNULIB's getline module.
libcvs_a_SOURCES += getline.h
EXTRA_DIST += getndelim2.h getndelim2.c

## For GNULIB's getndelim2 module.
EXTRA_DIST += getndelim2.h getndelim2.c

## For GNULIB's getnline module.
libcvs_a_SOURCES += getnline.h getnline.c

## For GNULIB's getpagesize module.
libcvs_a_SOURCES += getpagesize.h

## For GNULIB's gettext module.
libcvs_a_SOURCES += gettext.h

## For GNULIB's gettime module.
libcvs_a_SOURCES += gettime.c

## For GNULIB's minmax module.
libcvs_a_SOURCES += minmax.h

## For GNULIB's pathmax module.
libcvs_a_SOURCES += pathmax.h

## For GNULIB's save-cwd module.
libcvs_a_SOURCES += save-cwd.h save-cwd.c

## For GNULIB's setenv module.
libcvs_a_SOURCES += setenv.h

## For GNULIB's stat module.
libcvs_a_SOURCES += stat-macros.h

## For GNULIB's strcase module.
libcvs_a_SOURCES += strcase.h

## For GNULIB's strftime module.
libcvs_a_SOURCES += strftime.c strftime.h

## For GNULIB's time_r module.
libcvs_a_SOURCES += time_r.h

## For GNULIB's timespec module.
libcvs_a_SOURCES += timespec.h

## For GNULIB's unlocked-io module.
libcvs_a_SOURCES += unlocked-io.h

## For GNULIB's vasnprintf module.
libcvs_a_SOURCES += printf-args.h printf-parse.h vasnprintf.h

# For the vasprintf module from GNULIB.
libcvs_a_SOURCES += vasprintf.h

## For GNULIB's xalloc module.
libcvs_a_SOURCES += xalloc.h xmalloc.c

## For GNULIB's xalloc-die module.
libcvs_a_SOURCES += xalloc-die.c

## For GNULIB's xgetcwd module.
libcvs_a_SOURCES += xgetcwd.h xgetcwd.c

## For GNULIB's module xgethostname

libcvs_a_SOURCES += xgethostname.h xgethostname.c

## For GNULIB's xreadlink module.
libcvs_a_SOURCES += xreadlink.h xreadlink.c

# For the xsize module from GNULIB.
libcvs_a_SOURCES += xsize.h

## For GNULIB's yesno module.
libcvs_a_SOURCES += yesno.c yesno.h

# for backwards compatibility with the old makefiles
realclean: maintainer-clean
.PHONY: realclean
