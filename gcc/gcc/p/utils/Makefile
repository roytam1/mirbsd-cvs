# $MirOS: gcc/gcc/p/utils/Makefile,v 1.2 2005/03/28 00:05:06 tg Exp $
# Makefile for the GNU Pascal utilities
#
# Copyright (C) 2002-2005 Free Software Foundation, Inc.
#
# Author: Frank Heckenbach <frank@pascal.gnu.de>
#
# This file is part of GNU Pascal.
#
# GNU Pascal is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
#
# GNU Pascal is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with GNU Pascal; see the file COPYING. If not, write to the
# Free Software Foundation, 59 Temple Place - Suite 330, Boston, MA
# 02111-1307, USA.

# Variables to override
PC=gpc
CFLAGS=-O2 -g
PFLAGS=
UTILS_WARN=-W -Wall -Wmissing-prototypes -Wmissing-declarations
GCC_DIR=ERROR--GCC_DIR-MUST-BE-SET
exeext=
prefix=/usr/local
bindir=$(prefix)/bin
man1dir=$(prefix)/man/man1
INSTALL_PROGRAM=install -m 755
INSTALL_DATA=install -m 644
BUILD=unknown
HOST=unknown

srcdir=$(GCC_DIR)/p/utils
VPATH=$(srcdir)

# Internal variables
PFLAGS1=--executable-path=. --unit-path=$(GCC_DIR)/p/rts --unit-path=$(GCC_DIR)/p/units
EXE=binobj$(exeext) gpidump$(exeext)
EXE2=binobj gpidump
PC_WITH_FLAGS=$(PC) --automake --executable-file-name $(UTILS_WARN) $(subst -Wformat,,$(CFLAGS)) $(PFLAGS) $(PFLAGS1) `cat needed-options`

all: $(EXE)

# The Pascal source is not used, but we have to provide any.
# `-x Preprocessed-Pascal /dev/null' works as well, except on mingw.
needed-options: binobj.pas $(GCC_DIR)/p/version.h
	$(PC) $(UTILS_WARN) $(subst -Wformat,,$(CFLAGS)) $(PFLAGS) $(PFLAGS1) --print-needed-options "$<" 2> "$@" || true
	if grep '^[^-]' "$@" > /dev/null; then echo "needed-options: `cat "$@"`" >&2; rm -f "$@"; false; else true; fi

binobj$(exeext): binobj.pas needed-options
	$(PC_WITH_FLAGS) "$<"

gpidump$(exeext): gpidump.pas tree.inc needed-options
	$(PC_WITH_FLAGS) -I. -I "$(GCC_DIR)/p" "$<"

tree.inc: $(GCC_DIR)/version.c $(GCC_DIR)/tree.def $(GCC_DIR)/p/p-tree.def $(GCC_DIR)/p/module.c
	$(SHELL) "$(srcdir)/mk-t-inc" "$(GCC_DIR)" "$@"

install:
	for f in $(EXE); do \
	  rm -f $(bindir)/"$$f"; \
	  $(INSTALL_PROGRAM) "$$f" "$(bindir)/$$f"; \
	  chmod a+x $(bindir)/"$$f"; \
	done

clean:
	rm -f *.o *.i *.s *.gpi *.gpd $(EXE) $(EXE2) $(DOC) tree.inc needed-options
