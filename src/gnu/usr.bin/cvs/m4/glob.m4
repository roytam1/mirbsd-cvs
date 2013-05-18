# glob.m4 serial 3
dnl Copyright (C) 2005 Free Software Foundation, Inc.
dnl This file is free software; the Free Software Foundation
dnl gives unlimited permission to copy and/or distribute it,
dnl with or without modifications, as long as this notice is preserved.

# The glob module assumes you want GNU glob, with glob_pattern_p etc,
# rather than vanilla POSIX glob.  This means your your code should
# always include <glob.h> for the glob prototypes.

AC_DEFUN([gl_GLOB_SUBSTITUTE],
[
  gl_PREREQ_GLOB

  GLOB_H=glob.h
  AC_LIBSOURCES([glob.c, glob_.h, glob-libc.h])
  AC_LIBOBJ([glob])
  AC_SUBST([GLOB_H])
])

AC_DEFUN([gl_GLOB],
[ GLOB_H=
  AC_CHECK_HEADERS([glob.h], [], [GLOB_H=glob.h])

  if test -z "$GLOB_H"; then
    AC_CACHE_CHECK([for GNU glob interface version 1],
      [gl_cv_gnu_glob_interface_version_1],
[     AC_COMPILE_IFELSE(
[[#include <gnu-versions.h>
char a[_GNU_GLOB_INTERFACE_VERSION == 1 ? 1 : -1];]],
	[gl_cv_gnu_glob_interface_version_1=yes],
	[gl_cv_gnu_glob_interface_version_1=no])])

    if test "$gl_cv_gnu_glob_interface_version_1" = "no"; then
      GLOB_H=glob.h
    fi
  fi

  if test -z "$GLOB_H"; then
    AC_CACHE_CHECK([whether glob lists broken symlinks],
                   [gl_cv_glob_lists_symlinks],
[     if ln -s conf-doesntexist conf$$-globtest 2>/dev/null; then
        gl_cv_glob_lists_symlinks=maybe
      else
        # If we can't make a symlink, then we cannot test this issue.  Be
        # pessimistic about this.
        gl_cv_glob_lists_symlinks=no
      fi

      if test $gl_cv_glob_lists_symlinks = maybe; then
        AC_RUN_IFELSE(
AC_LANG_PROGRAM(
[[#include <stddef.h>
#include <glob.h>]],
[[glob_t found;
if (glob ("conf*-globtest", 0, NULL, &found) == GLOB_NOMATCH) return 1;]]),
          [gl_cv_glob_lists_symlinks=yes],
          [gl_cv_glob_lists_symlinks=no], [gl_cv_glob_lists_symlinks=no])
      fi])

    if test $gl_cv_glob_lists_symlinks = no; then
      GLOB_H=glob.h
    fi
  fi

  rm -f conf$$-globtest

  if test -n "$GLOB_H"; then
    gl_GLOB_SUBSTITUTE
  fi
])

# Prerequisites of lib/glob.*.
AC_DEFUN([gl_PREREQ_GLOB],
[ AC_REQUIRE([gl_CHECK_TYPE_STRUCT_DIRENT_D_TYPE])dnl
  AC_REQUIRE([AC_GNU_SOURCE])dnl
  AC_REQUIRE([AC_HEADER_DIRENT])dnl
  AC_CHECK_HEADERS_ONCE([sys/cdefs.h unistd.h])dnl
  AC_CHECK_FUNCS_ONCE([getlogin_r getpwnam_r])dnl
  :])
