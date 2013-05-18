# Makefile.am for texinfo.
# $MirOS$
# $Id$
# Process this file with automake to produce Makefile.in in all directories.
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

# Be sure we're using the right version of Automake.
AUTOMAKE_OPTIONS = 1.8

SUBDIRS = $(native_tools) info makeinfo util

# for gettext.
ACLOCAL_AMFLAGS = -I m4

# In case TEXINFO_MAINT is set during make distcheck; in this case, the
# simple doc-related files generated in info/ make distcleancheck fail.
distcleancheck_listfiles = \
  find -type f -exec sh -c 'test -f $(srcdir)/{} || echo {}' ';'

distclean-local:
	-test -d "$(native_tools)" && rm -rf "$(native_tools)"
