divert(-1)dnl
# $MirOS: contrib/gnu/libtool/m4salt.inc,v 1.5 2005/02/11 02:02:43 tg Exp $
# _MirOS: contrib/gnu/libtool/m4salt.inc,v 1.5 2005/02/11 02:02:43 tg Exp $
#-
# Copyright (c) 2004, 2005
# Free Software Foundation, Inc.
# Contributed by Thorsten "mirabile" Glaser.
#
# This file is licenced under the same terms and conditions as
# GNU autoconf, including the GPL exception.
#-
# m4salt - include m4sugar (from Autoconf 2.52) for Autoconf 2.13 as
# well as enough magic to make GNU Libtool 1.5 work with Autoconf in
# both the 2.13 and 2.59 version. Provide a way for libtool.m4 later
# on to distinguish whether stuff has been fnordified or not.

define([AC_m4salt_INIT],
[builtin([include], [m4sugar.inc])dnl

dnl Undo some damage
m4_copy_unm4([m4_builtin])
m4_copy_unm4([m4_changequote])
m4_copy_unm4([m4_decr])
m4_copy_unm4([m4_define])
m4_copy_unm4([m4_defn])
m4_copy_unm4([m4_divert])
m4_copy_unm4([m4_divnum])
m4_copy_unm4([m4_errprint])
m4_copy_unm4([m4_esyscmd])
m4_copy_unm4([m4_ifdef])
m4_copy([m4_if], [ifelse])
m4_copy_unm4([m4_incr])
m4_copy_unm4([m4_index])
m4_copy_unm4([m4_indir])
m4_copy_unm4([m4_len])
m4_copy_unm4([m4_patsubst])
m4_copy_unm4([m4_popdef])
m4_copy_unm4([m4_pushdef])
m4_copy_unm4([m4_regexp])
m4_copy_unm4([m4_sinclude])
m4_copy_unm4([m4_syscmd])
m4_copy_unm4([m4_sysval])
m4_copy_unm4([m4_traceoff])
m4_copy_unm4([m4_traceon])
m4_copy_unm4([m4_translit])
m4_copy_unm4([m4_undefine])
m4_copy_unm4([m4_undivert])

m4_ifndef([m4_tmpdir], [m4_define([m4_tmpdir], [/tmp])])dnl

dnl Another identifier
define([m4_PACKAGE_VERSION], [fnord_acsalt])dnl

])dnl # AC_m4salt_INIT

dnl AC_PROG_CXX()
dnl ----------------
dnl Forgiving copy of original AC_PROG_CXX
builtin([undefine], [AC_PROG_CXX])dnl
NOACLOCAL_DEFUN([AC_PROG_CXX],
[dnl from AC_PROG_CXX (autoconf 2.13)
dnl  --------------------------------
AC_CHECK_PROGS(CXX, $CCC c++ g++ gcc CC cxx cc++ cl, gcc)

dnl  from AC_PROG_CXX_WORKS (autoconf 2.13)
dnl  --------------------------------------
AC_MSG_CHECKING([whether the C++ compiler ($CXX $CXXFLAGS $LDFLAGS) works])
AC_LANG_CPLUSPLUS
AC_TRY_COMPILER([int main(){return(0);}], ac_cv_prog_cxx_works, ac_cv_prog_cxx_cross)
AC_MSG_RESULT($ac_cv_prog_cxx_works)
if test $ac_cv_prog_cxx_works = no; then
  AC_MSG_WARN([installation or configuration problem: C++ compiler cannot create executables.])
  CXX=false
else
  AC_MSG_CHECKING([whether the C++ compiler ($CXX $CXXFLAGS $LDFLAGS) is a cross-compiler])
  AC_MSG_RESULT($ac_cv_prog_cxx_cross)
  cross_compiling=$ac_cv_prog_cxx_cross
  AC_PROG_CXX_GNU

  if test $ac_cv_prog_gxx = yes; then
    GXX=yes
  else
    GXX=
  fi

dnl Check whether -g works, even if CXXFLAGS is set, in case the package
dnl plays around with CXXFLAGS (such as to build both debugging and
dnl normal versions of a library), tasteless as that idea is.
  ac_test_CXXFLAGS="${CXXFLAGS+set}"
  ac_save_CXXFLAGS="$CXXFLAGS"
  CXXFLAGS=
  AC_PROG_CXX_G
  if test "$ac_test_CXXFLAGS" = set; then
    CXXFLAGS="$ac_save_CXXFLAGS"
  elif test $ac_cv_prog_cxx_g = yes; then
    if test "$GXX" = yes; then
      CXXFLAGS="-g -O2"
    else
      CXXFLAGS="-g"
    fi
  else
    if test "$GXX" = yes; then
      CXXFLAGS="-O2"
    else
      CXXFLAGS=
    fi
  fi
fi
AC_LANG_C
])dnl # AC_PROG_CXX

dnl We don't have/want/need aclang.m4
define([AC_LANG_PUSH],
[AC_LANG_SAVE
ifelse([$1],
 [C], AC_LANG_C,
 [C++], AC_LANG_CPLUSPLUS)
])dnl # AC_LANG_PUSH

define([AC_LANG_POP],
[AC_LANG_RESTORE])dnl # AC_LANG_POP

define([AS_MESSAGE_LOG_FD], 5)dnl

dnl Initialisation of m4salt
dnl ------------------------

define([AC_m4salt_SPLIT],
[translit($1, ., [, ])])dnl

define([AC_m4salt_CANON],
[$1, $2])dnl

dnl AC_m4salt_VERIE(MAJOR1, MINOR1, MAJOR2, MINOR2, IFLOWER, IFGREATEROREQUAL)
define([AC_m4salt_VERIE],
[ifelse(builtin([eval], [$2 + $1 * 1000 < $4 + $3 * 1000]), [1],
 [$5], [$6])
])dnl

ifelse(m4_PACKAGE_VERSION, [fnord_acsalt],
[dnl We have already been called
],[
AC_m4salt_VERIE(AC_m4salt_CANON(AC_m4salt_SPLIT(AC_ACVERSION)),
		2, 50,
		[AC_m4salt_INIT
		define(AC_m4salt_OLD, [1])],
		[define(AC_m4salt_OLD, [0])])dnl
])dnl
