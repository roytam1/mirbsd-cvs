divert(-1)dnl
# $MirOS: contrib/gnu/libtool/m4salt.m4,v 1.3 2005/02/09 23:42:07 tg Exp $
#-
# Copyright (c) 2004, 2005
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
#
# Alternatively to these terms and conditions, this work may be han-
# dled as if it were covered by the same terms and conditions as the
# current version of GNU Autoconf, or versions derived from Autoconf
# 2.13, if it is part of an autoconf'd programme or an autotools re-
# placement/patchkit suite. The same exception clauses apply.
# The author hereby grants the "Free Software Foundation" permission
# to, under the standing copyright assignment, take over this script
# and licence it as they want.
#
# Below there is one modified excerpt from GNU Autoconf which is co-
# vered by the following GNU GPL exception clause:
#| As a special exception, the Free Software Foundation gives unli-
#| mited permission to copy, distribute and modify the configure
#| scripts that are the output of Autoconf. You need not follow the
#| terms of the GNU General Public License when using or distribu-
#| ting such scripts, even though portions of the text of Autoconf
#| appear in them. The GNU General Public License (GPL) does govern
#| all other use of the material that constitutes the Autoconf pro-
#| gram.
# The MirOS project and Thorsten Glaser hereby grant you the same.
#-
# m4salt - include m4sugar (from Autoconf 2.52) for Autoconf 2.13 as
# well as enough magic to make GNU Libtool 1.5 work with Autoconf in
# both the 2.13 and 2.59 version. Provide a way for libtool.m4 later
# on to distinguish whether stuff has been fnordified or not.

define([AC_m4salt_INIT],
[builtin([include], [m4sugar.m4])dnl

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

dnl The following macro is under the GPL with exception clause:
dnl AC_PROG_CXX()
dnl ----------------
dnl Forgiving copy of original AC_PROG_CXX
builtin([undefine], [AC_PROG_CXX])dnl
builtin([define], [NOACLOCAL_DEFUN], defn([AC_DEFUN]))dnl
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
])dnl
dnl End of GPL+exc licenced part.

dnl No Fortran 77 with autoconf-2.13 and MirLibtool
builtin([undefine], [AC_PROG_F77])dnl
NOACLOCAL_DEFUN([AC_PROG_F77],
[
])dnl

dnl Another identifier
define([m4_PACKAGE_VERSION], [fnord_acsalt])dnl

dnl We don't have/want/need aclang.m4
define([AC_LANG_PUSH],
[AC_LANG_SAVE
ifelse([$1],
 [C], AC_LANG_C,
 [C++], AC_LANG_CPLUSPLUS)
])])dnl # AC_LANG_PUSH

define([AC_LANG_POP],
[AC_LANG_RESTORE])dnl # AC_LANG_POP

define([AS_MESSAGE_LOG_FD], 5)dnl
])dnl

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
