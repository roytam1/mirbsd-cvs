# $MirBSD: contrib/gnu/libtool/configure.ac,v 1.7 2004/10/16 23:39:12 tg Exp $

## Process this file with autoconf to create configure. -*- autoconf -*-
# Copyright 2001, 2004
#	Free Software Foundation, Inc.
#
# This program is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
# 02111-1307  USA


## This is enough for MirLibtool
AC_PREREQ(2.13)



## ------------------------ ##
## Autoconf initialisation. ##
## ------------------------ ##
AC_INIT([ltmain.in])



## ------------------------ ##
## Automake Initialisation. ##
## ------------------------ ##
AM_INIT_AUTOMAKE([libtool], [1.5.10])


ACINCLUDE_M4_LIST="${srcdir}/acinclude.m4"
DIST_MAKEFILE_LIST=
AC_SUBST([ACINCLUDE_M4_LIST])
AC_SUBST([DIST_MAKEFILE_LIST])



## ---------------- ##
## compiler checks. ##
## ---------------- ##

# Use the specified CC and LD
AC_PROG_CC
AC_EXEEXT
AM_PROG_LD
AC_SUBST(LD)
AM_PROG_NM
AC_SUBST(NM)
AC_PROG_LN_S



## ----------------------- ##
## Libtool initialisation. ##
## ----------------------- ##
AC_LIBTOOL_DLOPEN
AC_PROG_LIBTOOL



## -------- ##
## Outputs. ##
## -------- ##
AC_OUTPUT([Makefile])
