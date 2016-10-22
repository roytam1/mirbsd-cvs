# longdouble.m4 serial 1 (gettext-0.12)
dnl Copyright (C) 2002-2003 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

dnl From Bruno Haible.
dnl Test whether the compiler supports the 'long double' type.
dnl Prerequisite: AC_PROG_CC

AC_DEFUN([gt_TYPE_LONGDOUBLE],
[
  dnl XXX this is wrong, Debian's autofools don't set ac_cv_type_long_double from AC_CHECK_SIZEOF any more
  AC_CHECK_SIZEOF(long double)
  gt_cv_c_long_double=$ac_cv_type_long_double
  if test x"$gt_cv_c_long_double" = x"yes"; then
    AC_DEFINE(HAVE_LONG_DOUBLE, 1, [Define if you have the 'long double' type.])
  fi
])
