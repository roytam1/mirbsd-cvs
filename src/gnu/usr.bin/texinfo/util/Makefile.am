# $MirOS$
# $Id$
# Makefile.am for texinfo/util.
# Run automake in .. to produce Makefile.in from this.
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

bin_PROGRAMS = ginstall-info texindex

# Use `ginstall-info' in the definition of PROGRAMS and in dependencies
# because automake generates an install-info target in every Makefile (a
# bug, IMHO, but this is easier than patching Automake.)
ginstall_info_SOURCES = install-info.c

# Transform `ginstall-info' to `install-info' before applying any
# user-specified name transformations.
transform = s/ginstall-info/install-info/; $(program_transform_name)

# Most of these are for fun.
#
EXTRA_DIST = fix-info-dir gen-dir-node
